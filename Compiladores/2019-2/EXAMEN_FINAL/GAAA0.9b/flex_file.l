%{
/* Ejemplo para una pequeña calculadora que permite trabajar con numeros enteros y reales con las operacionesbásicas de suma, resta, producto, division y trigonometricas como el seno y el coseno */

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tabla.tab.h"
#include <cstdio>

using namespace std;

%}
ID [a-zA-Z]+
DIGITO [0-9]


%%
[ \t\n]				;
{DIGITO}+("."{DIGITO}+)? { yylval.stype = (yytext);return(NUM);}
"crear"	{return(DEF);}
"llamar" {return(CALL);}
"mientras" 		{return MIENTRAS;}
"Programa"	{return PROGRAMA;}
"Inicio"		{return PROG_INICIO;}
"Fin"		{return PROG_FIN;}
"Si"		{return SI;}
"finSi"		{return FIN_SI;}
"Sino"		{return SINO;}
"Mientras"		{return MIENTRAS;}
"finMientras"		{return FIN_MIENTRAS;}
"Imprimir"	{return IMPRIMIR;}
"Desde"		{return DESDE;}
"finDesde"		{return FIN_DESDE;}
"Hasta"		{return HASTA;}
"Hacer"		{return HACER;}
"raiz"		{return RAIZ;}
"pot"		{return POT;}
{ID} 	{yylval.stype=strdup(yytext);return(ID);}
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
.            {return *yytext;}

%%
