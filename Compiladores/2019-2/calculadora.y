/*
Practica calificada N3
Alumno: Vasquez Espinoza, Luis
Desarrollo de la 1
Puede probar el compilador con la siguiente cadena:

-2.3 - 5 * (3/2 - 1.2); <- no olvidar el PUNTCOM
*/

%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void yyerror(char *);
int yylex();
#define YYSTYPE double /*double type for YACC stack*/
char lexema[60];
%}

%token NUM ID

%%
prog:	/* vacio */
	|	prog line;
	
line:	'\n'
	|	expr ';' '\n' {printf("Resultado: %g\n", $1);};

expr:	expr '+' term {$$ = $1 + $3;}
	|	expr '-' term {$$ = $1 - $3;}
	|	term {$$ = $1;};

term:	term '*' fact {$$ = $1 * $3;}
	|	term '/' fact {$$ = $1 / $3;}
	|	fact {$$ = $1;};

fact:	NUM {$$ = $1;}
	|	'-' NUM {$$ = -$2;}
	|	'(' expr ')' {$$ = $2;};
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
	
	/* Leyendo caracteres utiles */
	if(c == '.' || isdigit(c)){
		ungetc(c, stdin);
		scanf("%lf", &yylval);
		return NUM;
	}
	
	return c;
}

int main(){
	return yyparse();
}

