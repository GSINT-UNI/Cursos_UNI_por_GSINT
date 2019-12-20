%{
#include <stdio.h>
%}

%option noyywrap

CADENA [b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|w|x|y|z|' '|0-9]*
DIGITO [0-9]*
ERROR [a-z|0-9]*
COMENTARIOS [/][*][a-z|\n|0-9|' ']*[*][/]

%%
{DIGITO}+   printf("cadena que no usa vocales\n");
{COMENTARIOS}+   printf("comentario\n");
{ERROR}+   printf("error\n");
{CADENA}+   printf("cadena que no usa vocales\n");

%%

int main(int argc, char **argv)
{
   yylex();
   return 0;
}
