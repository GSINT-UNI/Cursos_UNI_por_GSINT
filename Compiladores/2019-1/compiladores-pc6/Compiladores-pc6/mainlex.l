%{
#include <stdio.h>
#include "main.tab.h"
%}

%%
"pepito" return TEXT;
\+	{return('+');}
\-	{return('-');}
\*	{return('*');}
\/	{return('/');}
\=	{return('=');}
\;	{return(';');}
\(	{return('(');}
\)	{return(')');}
\{	{return('{');}
\}	{return('}');}
\<	{return('<');}
\>	{return('>');}

[0-9]+ {return NUMBER;}
"If" {return IF;}
"Else" {return ELSE;}
[a-zA-Z]+ {return TEXT;}

%%
