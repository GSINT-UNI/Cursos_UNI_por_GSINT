%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lexema[60];
void yyerror(char *msg);
typedef struct{ char nombre[60]; double valor; int token;}tipoTS;
tipoTS TablaSim[100];

int nSim = 0;

typedef struct{int op; int a1; int a2; int a3;}tipoCodigo;
int cx=-1;
tipoCOdigo TCodigo[100];

void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp=0;
int GenVarTemp();
%}


%token PROGRAMA ID INICIO FIN NUM VARIABLE ASIGNAR SUMAR


%%



S : PROGRAMA ID ':' listadeclaracion INICIO listaInstr FIN '.' ;

listaInstr: instr listaInstr | ;

instr: ID {$$ = localizaSimb(lexema ID);}':' '=' expr {generaCodigo(ASIGNAR,$2,$5,'-');}';';
expr: expr '+'
expr
expr

