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
%x Comentario

%%


{DIGITO}  {yylval.stype=strdup(yytext);return(NUM);}
blank			{}

"mientras" 		{return(MIENTRAS);}
"Programa"	{return (PROGRAMA);}
"Inicio"		{return (PROG_INICIO);}
"Fin"		{return (PROG_FIN);}
"Si"		{return (SI);}
"finSi"		{return (FIN_SI);}
"Sino"		{return (SINO);}
"Mientras"		{return (MIENTRAS);}
"finMientras"		{return (FIN_MIENTRAS);}
"Imprimir"	{return (IMPRIMIR);}
"Desde"		{return (DESDE);}
"finDesde"		{return (FIN_DESDE);}
"Hasta"		{return (HASTA);}
"Hacer"		{return (HACER);}
"raiz"		{return (RAIZ);}
"pot"		{return (POT);}
"crearFunc"		{return (DEFINE);}
"llamarFunc"		{return (CALL);}


"+"			{return('+');}
"-"			{return('-');}
"*"			{return('*');}
"/"			{return('/');}
"^"			{return('^');}
"="			{return('=');}
";"			{return(';');}
","			{return(',');}
"("			{return('(');}
")"			{return(')');}
"{"			{return('{');}
"}"			{return('}');}
"<" 			{return('<');}
">" 			{return('>');}
{ID}                   	{yylval.stype=strdup(yytext);return(ID);}
"\n"                   	{return('\n');}
"/*"			{BEGIN(Comentario);}
<Comentario>"*/" {BEGIN(INITIAL);}
<Comentario>\n   { }
<Comentario>.    { }
.

%%
