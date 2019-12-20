%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char lexema[60];
void yyerror(char *msg);

typedef struct{
	char nombre[60];
	double valor;
	int token;
}tipoTS;

tipoTS TablaSim[200];
int nSim = 0;

typedef struct{
	int op;
	int a1;
	int a2;
	int a3;
}tipoCodigo;

int cx = -1;
tipoCodigo TCodigo[200];
void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp = 0;
int GenVarTemp();
void actualiza();
%}

%token ALGORIT DEMO ID INICIO FIN NUM VARIABLE ASIGNAR SUM RES MUL DIV PARENT RAIZ RAIZ_OP MAYOR MENOR MAYOR_IGUAL MENOR_IGUAL


%%
S: ALGORIT DEMO INICIO listaInstr FIN '.';

listaInstr: instr listaInstr | ;
instr: ID{$$=localizaSimb(lexema,ID);} '=' expr{generaCodigo(ASIGNAR,$2,$4,'°');}',';
expr: expr '+' term{int i = GenVarTemp(); generaCodigo(SUM,i,$1,$3); $$=i;};
expr: expr '-' term{int i = GenVarTemp(); generaCodigo(RES,i,$1,$3); $$=i;};
expr: term;
term: term '*' term2{int i = GenVarTemp(); generaCodigo(MUL,i,$1,$3); $$=i;};
term: term '/' term2{int i = GenVarTemp(); generaCodigo(DIV,i,$1,$3); $$=i;};
term: term2;
term2: RAIZ '(' fact ')' {int i = GenVarTemp(); generaCodigo(RAIZ_OP,i,$3,'°'); $$=i;};
term2: term3;
term3: term3 '<' fact{int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
term3: term3 '<' term4{int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
term3: term3 '>' fact{int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
term3: term3 '>' term4{int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
term3: term3 '<' '=' fact{int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '<' '=' term4{int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' fact{int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' term4{int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};
term3: fact;
term3: term4;
term4: '(' expr ')'{int i = GenVarTemp(); generaCodigo(PARENT,i,$2,$2); $$=i;};
fact: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);}; | RAIZ;
%%


int GenVarTemp(){
	char t[60];
	sprintf(t,"T%d",nVarTemp++);
	return localizaSimb(t,ID);
}


void generaCodigo( int op, int a1, int a2, int a3 ){
	cx++;
	TCodigo[cx].op = op;
	TCodigo[cx].a1 = a1;
	TCodigo[cx].a2 = a2;
	TCodigo[cx].a3 = a3;
}


int localizaSimb( char *nom, int tok ){
	int i;
	for( i=0; i<nSim; i++ ){
		if(!strcasecmp(TablaSim[i].nombre,nom))
		return i;
	}
	strcpy(TablaSim[nSim].nombre,nom);
	TablaSim[nSim].token = tok;
	if(tok==ID) TablaSim[nSim].valor = 0.0;
	if(tok==NUM) sscanf(nom,"%lf",&TablaSim[nSim].valor);
	nSim++;
	return nSim - 1;
}

void imprimeTablaSim(){
	int i;
	for( i = 0; i < nSim; i++ )
		printf("nombre=%s\ttok=%d\t\tvalor=%lf\n",TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
}

void ordenar_token(){
	tipoTS temp;
	int i, j;
	for( i=0; i<nSim; i++ ){
		for( j=i+1; j<nSim; j++ ){
			if( TablaSim[i].token>TablaSim[j].token ){
				strcpy(temp.nombre,TablaSim[i].nombre);
				temp.token = TablaSim[i].token;
				temp.valor = TablaSim[i].valor;
				strcpy(TablaSim[i].nombre,TablaSim[j].nombre);
				TablaSim[i].token = TablaSim[j].token;
				TablaSim[i].valor = TablaSim[j].valor;
				strcpy(TablaSim[j].nombre,temp.nombre);
				TablaSim[j].token = temp.token;
				TablaSim[j].valor = temp.valor; 
			}
		}
	}
}

void ordenar_nombre(){
	tipoTS temp;
	int i, j;
	for( i=0; i<nSim; i++ ){
		for( j=i+1; j<nSim; j++ ){
			if( TablaSim[i].nombre[0]>TablaSim[j].nombre[0] ){
				strcpy(temp.nombre,TablaSim[i].nombre);
				temp.token = TablaSim[i].token;
				temp.valor = TablaSim[i].valor;
				strcpy(TablaSim[i].nombre,TablaSim[j].nombre);
				TablaSim[i].token = TablaSim[j].token;
				TablaSim[i].valor = TablaSim[j].valor;
				strcpy(TablaSim[j].nombre,temp.nombre);
				TablaSim[j].token = temp.token;
				TablaSim[j].valor = temp.valor; 
			}
			if( TablaSim[i].nombre[0] == TablaSim[j].nombre[0] ){
				if( TablaSim[i].nombre[1]>TablaSim[j].nombre[1] ){
					strcpy(temp.nombre,TablaSim[i].nombre);
					temp.token = TablaSim[i].token;
					temp.valor = TablaSim[i].valor;
					strcpy(TablaSim[i].nombre,TablaSim[j].nombre);
					TablaSim[i].token = TablaSim[j].token;
					TablaSim[i].valor = TablaSim[j].valor;
					strcpy(TablaSim[j].nombre,temp.nombre);
					TablaSim[j].token = temp.token;
					TablaSim[j].valor = temp.valor; 
				}
			}
		}
	}
}


void imprimeTablaCod(){
	int i;
	for( i=0; i<=cx; i++ )
		printf("op=%d\ta1=%d\ta2=%d\ta3=%d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
}


void actualiza(){
	int i,a1,a2,a3,op,j,temp;
	for( i=0; i<=cx; i++ )
	{
		op = TCodigo[i].op;
		a1 = TCodigo[i].a1;
		a2 = TCodigo[i].a2;
		a3 = TCodigo[i].a3;
		if(op==ASIGNAR) TablaSim[a1].valor = TablaSim[a2].valor;
		if(op==SUM) TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
		if(op==RES) TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
		if(op==MUL) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
		if(op==DIV) 
		{
			if(TablaSim[a3].valor!=0) TablaSim[a1].valor = TablaSim[a2].valor/TablaSim[a3].valor;
			else printf("no se puede dividir entre 0\n");
		}
		if(op==MAYOR)
		{
			if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor = 1;
			else TablaSim[a1].valor = 0;
		}
		if(op==MENOR)
		{
			if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor = 1;
			else TablaSim[a1].valor = 0;
		}
		
		if(op==MAYOR_IGUAL)
		{
			if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor = 1;
			else TablaSim[a1].valor = 0;
		}
		if(op==MENOR_IGUAL)
		{
			if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor = 1;
			else TablaSim[a1].valor = 0;
		}
		if(op==PARENT) TablaSim[a1].valor = TablaSim[a2].valor;
		if(op==RAIZ_OP) TablaSim[a1].valor=pow(TablaSim[a2].valor,0.5);
	}
}


void yyerror(char *msg){
	printf("ERROR: %s\n",msg);
}

int EsPalabraReservada(char lexema[]){
	if(strcasecmp(lexema,"Algoritmo")==0) return ALGORIT;
	if(strcasecmp(lexema,"Demo")==0) return DEMO;	
	if(strcasecmp(lexema,"inicioAlgoritmo")==0) return INICIO;
	if(strcasecmp(lexema,"finAlgoritmo")==0) return FIN;
	if(strcasecmp(lexema,"raiz")==0) return RAIZ;
	return ID;
}


int yylex(){
	char c; int i;
	while(1){
		c = getchar();
		if(c==' ') continue;
		if(c=='\t') continue;
		if(c=='\n') continue;
		if(isdigit(c)){
			i = 0;
			do{
				lexema[i++] = c;
				c = getchar();
			}while(isdigit(c));
			ungetc(c,stdin);
			lexema[i] = '\0';
			return NUM;
		}

		if(isalpha(c)){
			i = 0;
			do{
				lexema[i++] = c;
				c = getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i] = '\0';
			return EsPalabraReservada(lexema);
		}
		return c;
	}
}


int main(){
	if(!yyparse()) printf("\nLa cadena es valida\n");
	else printf("\nLa cadena es invalida\n");
	printf("\n1)\n");
	printf("tabla de simbolos:\n"); imprimeTablaSim();

	ordenar_token();
	printf("\n2)\n");
	printf("\ntabla ordenada por token:\n"); imprimeTablaSim();	
	ordenar_nombre();
	printf("\ntabla ordenada por nombre:\n"); imprimeTablaSim();


	printf("\n3)\n");
	printf("tabla de código:\n"); imprimeTablaCod();

	actualiza();
	printf("\n4)\n");
	printf("tabla actualizada:\n"); imprimeTablaSim();
	printf("\n");
}

