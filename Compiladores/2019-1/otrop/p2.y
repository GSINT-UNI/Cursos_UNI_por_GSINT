/*
Examen Parcial - Compiladores
Alumno: Vasquez Espinoza, Luis
Preg. 2
*/

%{
#include<stdio.h>
#include<string.h>
void yyerror(char *);
#define YYSTYPE double /*double type for YACC stack*/
char lexema[60];
%}

%token NUM ID

%%
prog:	/* vacio */
	|	prog line;
	
line:	'\n'
	|	op '\n';

op:		op op '+'
	|	op op '-'
	|	op op '*'
	|	op op '/'
	|	NUM;
%%

void yyerror(char *mgs){
    printf("error:%s",mgs);
}


int yylex(void){
	int c;

	/* Descartando los caracteres inutiles (como yo) */
	int continueFlag = 1;
	
	while(continueFlag){
		c = getchar();
		if(!(c == ' ' || c == '\t')){
			continueFlag = 0;
		}
	}
	
	if (isdigit(c)){
		int decimalFlag = 0;
		int decimalReaded = 0;
		int i = 0;
		do{
			if (decimalFlag){decimalReaded = 1;}
			lexema[i++]=c;
			c=getchar();
			if( c == '.' || c == 'e' || c == 'E' ){decimalFlag = 1;}
		}while((isdigit(c)) || (( c == '.' || c == 'e' || c == 'E' )&&(!decimalReaded)));

		ungetc(c, stdin);
		lexema[i] = 0;
		return NUM;
	}
	return c;
}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida\n");
	return 0;
}

