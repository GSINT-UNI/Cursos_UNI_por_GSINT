%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include<math.h>
char lexema[60];
void yyerror(char *msg);
void actualiza();

int bucle_activado=0;
int bucleF=0;
//tabla de simbolos
typedef struct{
  char nombre [60];
  double valor ;
  int token;
}tipoTS;


tipoTS TablaSim[100];
int nSim=0;

//tabla de codigo
typedef struct{
  int op;
  int a1;
  int a2;
  int a3;
}tipocodigo;

int posicion_for=0;
int cota_inferior=0;
int cota_superior=0;

int cx=-1;
tipocodigo TCodigo[100];
void generarCodigo(int , int ,int , int);
int localizaSimb(char *,int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();

int asignar_cotas(int x,int d){
	cota_inferior = (int)TablaSim[x].valor;
	cota_superior = (int)TablaSim[d].valor;
}

%}
%token DESDE HASTA HACER PROGRAMA ID INICIO FIN NUM VARIABLE SI SINO ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR MAYOR MENOR IGUAL MAYOR_IGUAL MENOR_IGUAL IF ENTONCES SALTARF1 SALTARF2 IMPRIMIR PARENTESIS BUCLE BUCLE_1 BUCLE_2 SALTARF3 SQRT RAIZ

%%

s : PROGRAMA ID ';'  INICIO listaInstr FIN '.' ;

listaInstr: asignacion listaInstr | bloque_if listaInstr |bucle_for listaInstr|imprimir listaInstr |;


bloque_if: SI '('condicion')' {printf("generando En el bloque_if...\n");generarCodigo(SALTARF1,$3,'-','-');printf("$3 es %d\n",$3);$$=cx;} ENTONCES '{' listaInstr '}' {generarCodigo(SALTARF2,'?','-','-');printf("Saltarf2 generando en bloque_if, ? es %d\n",'?');$$=cx;} {TCodigo[$5].a2=cx+1;printf("Valor de $5: %d Valor de cx: %d TCodigo[$5].a2 es %f \n",$5,cx,(double)cx+1);} otro {printf("$10 es %d, TCodigo[$10].a1 sera %d\n",$10,cx+1);;TCodigo[$10].a1=cx+1;};
otro: SINO '{' listaInstr '}'|  ;

condicion: expr '>' expr{int i = GenVarTemp(); generarCodigo(MAYOR,i,$1,$3); $$=i;};
condicion: expr '<' expr{int i = GenVarTemp(); generarCodigo(MENOR,i,$1,$3); $$=i;};
condicion: expr '=''=' expr{int i = GenVarTemp(); generarCodigo(IGUAL,i,$1,$4); $$=i;};
condicion: expr '<''>' expr;
condicion: expr '>''=' expr{int i = GenVarTemp(); generarCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
condicion: expr '<''=' expr{printf("genero codigo En la condicion...\n");int i = GenVarTemp(); generarCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};

imprimir: IMPRIMIR expr {generarCodigo(IMPRIMIR,$2,'-','-');}{ printf("Visualizando:=%d\n",$2);}';';


asignacion: ID {$$=localizaSimb(lexema,ID);}':''=' expr {printf("generando en asignacion...\n");;generarCodigo(ASIGNAR,$2,$5,'-');}';';
expr: expr '+' term { int i=GenVarTemp();generarCodigo(SUMAR,i,$1,$3);$$=i;};
expr: expr '-' term{ int i=GenVarTemp();generarCodigo(RESTAR,i,$1,$3);$$=i;}; 
expr:term;
term: term '*' fact{int i = GenVarTemp(); generarCodigo(MULTIPLICAR,i,$1,$3); $$=i;};
term: term '/' fact{int i = GenVarTemp(); generarCodigo(DIVIDIR,i,$1,$3); $$=i;};
term: fact;

fact: '(' expr ')'{printf("Generando en parentesis...\n");int i = GenVarTemp(); generarCodigo(PARENTESIS,i,$2,'-'); $$=i;};
fact: element;

element: SQRT '(' number ')' {printf("Generando en parentesis...\n");int i = GenVarTemp(); generarCodigo(RAIZ,i,$3,'-'); $$=i;};
element: number

number:NUM {$$=localizaSimb(lexema,NUM);}|ID{$$=localizaSimb(lexema,ID);};


bucle_for: DESDE number HASTA number HACER {bucleF=100;}{generarCodigo(SALTARF3,$2,$4,'-');posicion_for=cx;$$=cx;} '{' listaInstr '}' {generarCodigo(BUCLE,'?','-','-');$$=cx;}{TCodigo[$7].a3=cx;}{printf("$11 es %d \n",$11);TCodigo[$11].a1=cx+1;TCodigo[$11].a2=posicion_for;};


%%

int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,ID);
}

void generarCodigo(int op, int a1,int a2, int a3){
  cx++;
  //printf("XD %d\n",cx);
  TCodigo[cx].op=op;
  TCodigo[cx].a1=a1;
  TCodigo[cx].a2=a2;
  TCodigo[cx].a3=a3;
}

int localizaSimb(char *nom,int tok){
  int i;
  for (i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token=tok;
  if (tok==ID) TablaSim[nSim].valor=0.0;
  if (tok==NUM) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim-1;
}

void imprimeTablaSim(){
  int i;
  for ( i=0;i<nSim;i++){
    printf("%d nombre=%s tok=%d valor=%lf\n", i , TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for ( i=0;i<=cx;i++){
    printf("%d a1=%d a2=%d a3=%d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  	//printf("Holi, a1_VALOR = %d \n",TablaSim[TCodigo[i].a1].valor);
	//printf("Holi, a2_VALOR = %d \n",TablaSim[TCodigo[i].a2].valor);
	//printf("Holi, a3_VALOR = %d \n",TablaSim[TCodigo[i].a3].valor);

  }
}

void yyerror(char *msg){
  printf("ERROR:%s \n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera may y minusc
  //strcasecmp ignora may de min
  if (strcasecmp(lexema,"Program")==0) return PROGRAMA;
  if (strcasecmp(lexema,"Begin")==0) return INICIO;
  if (strcasecmp(lexema,"End")==0) return FIN;
  if (strcasecmp(lexema,"Si")==0) return SI;
  if (strcasecmp(lexema,"Sino")==0) return SINO;
  if (strcasecmp(lexema,"Entonces")==0) return ENTONCES;
  if(strcasecmp(lexema,"Imprimir")==0) return IMPRIMIR;
  if(strcasecmp(lexema,"Desde")==0) return DESDE;
  if(strcasecmp(lexema,"Hasta")==0) return HASTA;
  if(strcasecmp(lexema,"Hacer")==0) return HACER;
  if(strcasecmp(lexema,"raiz")==0) return SQRT;

  return ID;
}

int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(c=='\t') continue;
		
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalpha(c));
			ungetc(c, stdin);
			lexema[i]=0;
			
			return EsPalabraReservada(lexema);
		}
		if(isdigit(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c, stdin);
			lexema[i]=0;
			return NUM;
		}
		return c;
	}
}

void actualiza(){
	int i,a1,a2,a3,op,j,temp;
	printf("######## cx = %d ######\n",cx);
	for( i=0; i<=cx; i++ )

	{
		printf("******* Iteracion %d \n: ********",i);
		op = TCodigo[i].op;
		a1 = TCodigo[i].a1;
		a2 = TCodigo[i].a2;
		a3 = TCodigo[i].a3;
    if(op==MAYOR){
    		printf("Detecto mayor...\n");
    				  //printf("Holi, a1 = %d \n",TablaSim[a1].valor);
			          //printf("Holi, a2 = %d \n",TablaSim[a2].valor);
			          //printf("Holi, a3 = %d \n",TablaSim[a3].valor);

         if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MENOR){
    	    		printf("Detecto menor...\n");

         if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MAYOR_IGUAL){
    	    		printf("Detecto mayor igual...\n");

         if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MENOR_IGUAL){
    	    	    		printf("Detecto menor igual...\n");
    	    	    		printf("a1=%d a2=%d a3=%d TablaSim[a2].valor=%f TablaSim[a3].valor=%f\n",a1,a2,a3,TablaSim[a2].valor,TablaSim[a3].valor);
         if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==IGUAL){
    	    	   	printf("Detecto igualdad...\n");

    	printf("Asignando valor a la variable...\n");
         if(TablaSim[a2].valor==TablaSim[a3].valor)TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }

		if(op==SUMAR){
			printf("Suma...\n"); 
			printf("a1=%d  a2=%d a3=%d TablaSim[a1].valor=%f TablaSim[a2].valor=%f TablaSim[a3].valor=%f\n",a1,a2,a3,TablaSim[a1].valor,TablaSim[a2].valor,TablaSim[a3].valor);
			TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
		}
		if(op==RESTAR){printf("Resta...\n") ;TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;}	
		if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
   	 	if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
   	 	if(op==RAIZ) {TablaSim[a1].valor = sqrt(TablaSim[a2].valor);}

		if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;
		if(op==SALTARF1){
			printf("Bloque if, SALTARF1\n");
			printf("a1=%d a2=%d TablaSim[a1].valor=%f\n",a1,a2,TablaSim[a1].valor);

        	if(TablaSim[a1].valor==0){printf("En saltar f1, la condicion no se cumplio"); i=a2-1;printf("i es %d , a2 es %d \n",i,a2); };
    		printf("La siguiente operacion: %d\n",TCodigo[i+1].op);
    	}
    	if(op==SALTARF2){ printf("Detecto SALTARF2...\n");printf("a1 es %d, i sera %d\n",a1,a1-1);i=a1-1;
    	    		printf("La siguiente operacion: %d\n",TCodigo[i+1].op);
    	}
		if(op==SALTARF3)
		{
			if(!bucle_activado)
				asignar_cotas(a1,a2);
			bucle_activado = 1;
			printf("Entrando a SALTARF3...\n");
			printf("a1=%d  a2=%d a3=%d TablaSim[a1].valor=%f TablaSim[a2].valor=%f\n",a1,a2,a3,TablaSim[a1].valor,TablaSim[a2].valor);
			printf("cota_inferior=%d, cota_superior=%d \n",cota_inferior,cota_superior);
			if(cota_inferior <= cota_superior){
				cota_inferior++;	
			}
			else{
				bucle_activado = 0;
				i = a3 - 1;
			}
		}
		if(op==BUCLE) {printf("Entrando a BUCLE.....\n");printf("a1=%d\n",a1);
			if(bucle_activado){
				printf("i sera %d \n",a2-1);
				i = a2-1;
			}
			else{
				i = a1-1;
			}
		}
    	if(op==ASIGNAR) {
    	printf("Detecto asignar ...\n");
    	//printf("TablaSim[a1].valor antes de su asignacion %f \n",TablaSim[a1].valor);
    	//printf("TablaSim[a2].valor antes de su asignacion %f \n",TablaSim[a2].valor);
    	printf("a1 vale %d a2 vale %d, TablaSim[a2].valor vale %f \n",a1,a2,TablaSim[a2].valor);
    	TablaSim[a1].valor = TablaSim[a2].valor;
    	//printf("TablaSim[a1].valor se le asigno %f \n",TablaSim[a1].valor);
    	//printf("TablaSim[a2].valor se le asigno %f \n",TablaSim[a2].valor);


	}
	printf("tabla de simbolos antes de actualizarse\n");

		imprimeTablaSim();

			printf("********************************\n\n",i);

}

}

int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
		printf("tabla de codigos\n");
			imprimeTablaCod();

	printf("tabla de simbolos antes de actualizarse\n");
	imprimeTablaSim();	
	printf("*********************");
	actualiza();
	printf("tabla de codigos\n");
	imprimeTablaCod();
	printf("tabla de simbolos\n");
	imprimeTablaSim();


	return 0;
}





