%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
char lexema[60];
void yyerror(char *msg);

typedef struct
{
	char nombre[60];
	double valor;
	int token;
}tipoTS;

tipoTS TablaSim[100];
int nSim = 0;

typedef struct
{
	int op;
	int a1;
	int a2;
	int a3;
}tipoCodigo;

int cx = -1;
tipoCodigo TCodigo[100];
void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp = 0;
int bucleW,bucleF;
int GenVarTemp();
void InterpretaCodigo();
int linea = 0;

%}

%token ID ABRE CIERRA PROGRAMA NUM VARIABLE ASIGNAR SUMA RESTA MULTIPLICA DIVIDE POTENCIA PARENTESIS 
%token  SI SINO SINOSI SALTARF1 SALTARF2 SALTARF3 MIENTRAS IMPRIMIR PARA HASTA BUCLE
%token MAYOR MENOR IGUAL MAYOR_IGUAL MENOR_IGUAL
%token OPSUMAR OPRESTAR OPMULTIPLICAR DESDE MENSAJE1 MENSAJE2 MENSAJE3 COMILLA
%%

comienzo: PROGRAMA ID ABRE listaInstruccion CIERRA;

bloque: listaInstruccion |  instruccion bloque | ; 

listaInstruccion: instruccion listaInstruccion | ;
instruccion: imprimir |imprimir ';' ;
instruccion: VARIABLE vrble ';' | ID {$$=localizaSimb(lexema,ID);} '=' level1{generaCodigo(ASIGNAR,$2,$4,'-');} ';';

imprimir: IMPRIMIR level1 {generaCodigo(IMPRIMIR,$2,'-','-');}{ printf("s=%d\n",$2);}| IMPRIMIR COMILLA MENSAJE1 MENSAJE2 MENSAJE3 COMILLA{generaCodigo(IMPRIMIR,$2,'-','-');}{printf("No hay suma\n");};

vrble: ID {$$=localizaSimb(lexema,ID);} '=' level1{generaCodigo(ASIGNAR,$2,$4,'-'); } terminal vrble|;
terminal: ','|;
//$$ Almacena de valor de retorno de la produccion
instruccion: SI cond {generaCodigo(SALTARF1,$2,'?','-');$$=cx;} ABRE bloque {generaCodigo(SALTARF2,'?','-','-');$$=cx;}{TCodigo[$3].a2=cx+1;} CIERRA otro {TCodigo[$6].a1=cx+1;};

otro:  SINO SI cond {generaCodigo(SALTARF1,$3,'?','-');$$=cx;}  bloque {generaCodigo(SALTARF2,'?','-','-');$$=cx;}{TCodigo[$3].a2=cx+1;} SINO instruccion;


instruccion: SUMA DESDE ID HASTA ID {bucleF=100; }{generaCodigo(SALTARF3,$3,$5,'-');$5=100;} bloque {generaCodigo(BUCLE,bucleF,'-','-');}{TCodigo[$8].a3=cx;}{TCodigo[$10].a1=cx+1;};

cond: level1 '>' level1{int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
cond: level1 '<' level1{int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
cond: level1 '=' level1{int i = GenVarTemp(); generaCodigo(IGUAL,i,$1,$3); $$=i;};
cond: level1 '<''>' level1;
cond: level1 '>''=' level1{int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
cond: level1 '<''=' level1{int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};

level1: level1 '+' level2{int i = GenVarTemp(); generaCodigo(SUMA,i,$1,$3); $$=i;};
level1: level1 '-' level2{int i = GenVarTemp(); generaCodigo(RESTA,i,$1,$3); $$=i;};
level1: level2;

level2: level2 '*' level3{int i = GenVarTemp(); generaCodigo(MULTIPLICA,i,$1,$3); $$=i;};
level2: level2 '/' level3{int i = GenVarTemp(); generaCodigo(DIVIDE,i,$1,$3); $$=i;};
level2: level3;

level3: level3 '^' level5{int i = GenVarTemp(); generaCodigo(POTENCIA,i,$1,$3); $$=i;};
level3: level4;

level4: '(' level1 ')'{int i = GenVarTemp(); generaCodigo(PARENTESIS,i,$2,'-'); $$=i;};
level4: level5;

level5: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);};


%%

void InterpretaCodigo()
{
	int i,a1,a2,a3,op;
	printf("cx = %d\n",cx);
	for(i=0; i<=cx; i++)
	{
		op = TCodigo[i].op;
		a1 = TCodigo[i].a1;
		a2 = TCodigo[i].a2;
		a3 = TCodigo[i].a3;

		if(op==MAYOR)
		{
			if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
			TablaSim[a1].valor=0;
		}
		if(op==MENOR)
		{
			if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
			TablaSim[a1].valor=0;
		}
		if(op==MAYOR_IGUAL)
		{
			if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
			TablaSim[a1].valor=0;
		}
		if(op==MENOR_IGUAL)
		{
			if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
			TablaSim[a1].valor=0;
		}
		if(op==IGUAL)
		{
			if(TablaSim[a2].valor==TablaSim[a3].valor)TablaSim[a1].valor=1;
			else
			TablaSim[a1].valor=0;
		}
		if(op==SUMA) TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
		if(op==RESTA) TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
		if(op==MULTIPLICA) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
		if(op==DIVIDE) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
		if(op==SALTARF1)
		{		
			if(TablaSim[a1].valor==0) i=a2-1;
		}
		if(op==SALTARF2) i=a1-1;
		if(op==SALTARF3)
		{
			if(TablaSim[a1].valor==TablaSim[a2].valor) i=a3-1;
		}
		if(op==BUCLE) i=a1;
		if(op==OPSUMAR) i=a1;
		if(op==OPRESTAR) i=a1;
		if(op==OPMULTIPLICAR) i=a1;
		if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;
		if(op==ASIGNAR) TablaSim[a1].valor = TablaSim[a2].valor;
		if(op==IMPRIMIR) printf("%lf\n",TablaSim[a1].valor);
	}
}

int GenVarTemp()
{
	char t[60];
	sprintf(t,"_T%d",nVarTemp++);
	return localizaSimb(t,ID);
}

void generaCodigo(int op, int a1, int a2, int a3)
{
	cx++;
	TCodigo[cx].op = op;
	TCodigo[cx].a1 = a1;
	TCodigo[cx].a2 = a2;
	TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok)
{
	int i;
	for(i=0; i<nSim; i++)
	{
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

void imprimeTablaSim()
{
	int i;
	for(i=0; i<nSim; i++ )
		printf("%d\tnombre = %s\ttok = %d\tvalor = %lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
}

void imprimeTablaCod()
{
	int i;
	for(i=0; i<=cx; i++)
		printf("%d\ta1 = %d\ta2 = %d\ta3 = %d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3 );
}

void yyerror(char *msg)
{
	printf("ERROR: %s\n",msg);
}

int EsPalabraReservada(char lexema[])
{
	if(strcasecmp(lexema,"Programa")==0) return PROGRAMA;
	if(strcasecmp(lexema,"Var")==0) return VARIABLE;
	if(strcasecmp(lexema,"Si")==0) return SI;
	if(strcasecmp(lexema,"si")==0) return SI;
	if(strcasecmp(lexema,"Sumar")==0) return SUMA;
	if(strcasecmp(lexema,"Restar")==0) return RESTA;
	if(strcasecmp(lexema,"Multiplicar")==0) return MULTIPLICA;
	if(strcasecmp(lexema,"Dividir")==0) return DIVIDE;
	if(strcasecmp(lexema,"desde")==0) return DESDE;
	if(strcasecmp(lexema,"hasta")==0) return HASTA; 
	if(strcasecmp(lexema,"Imprimir")==0) return IMPRIMIR;
	if(strcasecmp(lexema,"Sino")==0) return SINO;
	if(strcasecmp(lexema,"No")==0) return MENSAJE1;
	if(strcasecmp(lexema,"hay")==0) return MENSAJE2;
	if(strcasecmp(lexema,"suma")==0) return MENSAJE3;
	return ID;
}

int yylex()
{
	char c; int i;
	while(1)
	{
		c = getchar();
		if(c==' ') continue;
		if(c=='\t') continue;
		if(c=='\n')
		{		
			linea++;
			continue;
		}
		if(c=='[') return ABRE;
		if(c==']') return CIERRA;
		if(c=='"') return COMILLA;
		if(isdigit(c))
		{
			i = 0;
			do
			{
				lexema[i++] = c;
				c = getchar();
			}while(isdigit(c));
		
			ungetc(c,stdin);
			lexema[i] = '\0';
			return NUM;
		}

		if(isalpha(c))
		{
			i = 0;
			do
			{
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

int main()
{
	if(!yyparse()) printf("Cadena válida\n");
	else printf("Cadena inválida\nError el la línea %d\n",linea);
	printf("\nTabla de Símbolos:\n"); imprimeTablaSim();
	printf("\nTabla de Códigos\n"); imprimeTablaCod();
	InterpretaCodigo();
	printf("\nDespués de interpretar código: Tabla de simbolos:\n"); imprimeTablaSim();
}




