%{
/* Ejemplo para una pequeña calculadora que permite trabajar con numeros enteros y reales con las operacionesbásicas de suma, resta, producto, division y trigonometricas como el seno y el coseno */

#include <stdio.h>
#include <stdlib.h>
#include "final.tab.h"
int nlines=0;
%}

DIGITO [0-9]
ID [a-zA-Z][a-zA-Z0-9_]*
blank [ \t]+
STRING \"[{ID}{blank}:]*\"
%x Comentario

%%


{DIGITO}+("."{DIGITO}+)?  {yylval.stype=strdup(yytext);return(NUM);}
blank			{}
"si"			{return(SI);}
"sino"			{return(SINO);}
"para" 			{return(PARA);}
"mientras" 		{return(MIENTRAS);}
"+"			{return('+');}
"-"			{return('-');}
"*"			{return('*');}
"/"			{return('/');}
"^"			{return('^');}
"raiz" 			{return(RAIZ);}
"="			{return('=');}
";"			{return(';');}
","			{return(',');}
"("			{return('(');}
")"			{return(')');}
"{"			{return('{');}
"}"			{return('}');}
"<" 			{return('<');}
">" 			{return('>');}
"!" 			{return('!');}
"&"			{return(AND);}
"||"			{return(OR);}
{STRING}		{yylval.stype=strdup(yytext);return(STRING);}
{ID}                   	{yylval.stype=strdup(yytext);return(ID);}
"\n"                   	{return(ENTER);}
"/*"			{BEGIN(Comentario);}
<Comentario>"*/" {BEGIN(INITIAL);}
<Comentario>\n   { }
<Comentario>.    { }
.

%%
