%{
#include <stdio.h>
#include <string.h>
char lexema[100];
void yyerror(char *);
%}

%token NUM PUNTO 

%%
instruccion: instruccion NUM PUNTO NUM ;
instruccion: ;
%%

void yyerror(char *mgs){
	printf("error: %s\n",mgs);
}
int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c=='.') return PUNTO;
		
		if(isdigit(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c,stdin);
			lexema[i]=0;
			return NUM;
		}
		return c;
	}
}
int main(){
	if(!yyparse()) 
		printf("cadena valida\n");
	else 
		printf("cadena invalida\n");
	return 0;
}
