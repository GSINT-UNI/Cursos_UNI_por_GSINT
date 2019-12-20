%{
#include<stdio.h>
#include<string.h>
#include <ctype.h>
char lexema[255];
//void yyerror(char *);
%}

%token ID
%%
instruccion: instruccion ID;
instruccion: ;
%%

void yyerror(){
	printf("error\n");
}

int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			
			ungetc(c,stdin);
			lexema[i]==0;
			return ID;
		}
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida...\n");
	else printf("cadena invalida \n");
	return 0;
}