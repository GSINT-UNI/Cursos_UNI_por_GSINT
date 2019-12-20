

%{

#include <stdio.h>

%}

%option noyywrap

DIGITO [0-9]
ID     [a-z][a-z0-9]*
ID2  [A-Z]
COM  [/][/].*

%%

{DIGITO}+  printf("Numero entero\n");

{DIGITO}+"."{DIGITO}+  printf("Numero Decimal\n");

{ID} 	printf("identificador\n"); 

{ID2}+{ID} printf("identificador con mayuscula\n");

{COM} printf("Comentario\n");

%%

int main(int argc, char **argv){

	yylex();
	return 0;
}
