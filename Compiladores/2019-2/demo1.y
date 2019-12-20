%{
#include<stdio.h>
#include<string.h>
#include <ctype.h>
char lexema[255];
void yyerror();
%}

%token ID NUM PUNTCOM INICIO FIN
%%

raiz: INICIO instruccion FIN;
instruccion: instruccion ID '=' eval PUNTCOM;
instruccion: ;
eval: factor '+' factor;
factor: NUM | ID;

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
		if(c==';') return PUNTCOM;
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			
			ungetc(c,stdin);
			if(strcmp(lexema,"INICIO")==0) return INICIO;
			if(strcmp(lexema,"FIN")==0) return FIN;
			lexema[i]==0;	
			
			return ID;
		}
		
		if(isdigit(c)){
			int i = 0;
			do{
				lexema[i++] = c;
				c = getchar();
			}while(isdigit(c));
			
			ungetc(c,stdin); // devuelve el caracter a la entrada estandar
			lexema[i]=0;
			return NUM;
		}		
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida...\n");
	else printf("cadena invalida \n");
	return 0;
}
