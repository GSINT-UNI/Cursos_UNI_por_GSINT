%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTCOM MAS MENOS POR DIVISION ABRE CIERRA POTENCIA COMA

%%

inst: ID IGUAL lista PUNTCOM | ;
lista: ABRE lista CIERRA | ABRE lista CIERRA operador lista | MENOS lista1 | lista1;
lista1: lista2 MAS lista1 | lista2 MENOS lista1 | lista2 MAS ABRE lista1 CIERRA | lista2 MENOS ABRE lista1 CIERRA | lista2;
lista2: lista2 POR NUM | lista2 DIVISION NUM | lista2 POR ABRE lista1 CIERRA | lista2 DIVISION ABRE lista1 CIERRA | lista3;
lista3: lista3 POTENCIA NUM | lista3 POTENCIA ABRE lista1 CIERRA | NUM | ID | MENOS NUM;
operador: MAS | MENOS | POR | DIVISION | POTENCIA;

%%

void yyerror(char *mgs){
	printf("error: %s\n",mgs);
}
int yylex()
{
	char c;
	while(1)
	{
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(c==',') return COMA;
		if(c==';') return PUNTCOM;
		if(c=='=') return IGUAL;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return POR;
		if(c=='/') return DIVISION;
		if(c=='(') return ABRE;
		if(c==')') return CIERRA;
		if(c=='^') return POTENCIA;
		if(isalpha(c))
		{
			int i=0;
			do
			{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]=0;
			return ID;
		}

		if(isdigit(c))
		{
			int i=0, coma=0;
			do
			{
				lexema[i++]=c;
				c=getchar();
				if( c==',' && coma==0 )
				{
					coma++;
					lexema[i++]=c;
					c=getchar();
					if(!isdigit(c) ) return c;
				}
				else if( c==',') return c;
			}while(isdigit(c) || c==',');
			ungetc(c,stdin);
			lexema[i]=0;
			return NUM;
		}
		return c;
	}
}


int main()
{
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
	return 0;
}


