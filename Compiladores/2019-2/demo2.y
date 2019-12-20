%{
#include<stdio.h>
#include<string.h>
#include <ctype.h>
char lexema[255];
void yyerror();
%}

%token NUM
%%
instruccion: instruccion factor '+' factor ';';
instruccion: ;
factor: NUM | '-'NUM
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
		if(isdigit(c)){
			int i=0;
			int complex_flag=0;
			do{
				lexema[i++]=c;
				c=getchar();
			if(c=='i'){
				printf("Complejo\n");
				lexema[i++]=c;
					}
				
			}while(isdigit(c));	

			printf("Saliendo...%s\n",lexema);		
			ungetc(c,stdin);
			lexema[i]==0;
			printf("Saliendo despues del lexema...%s\n",lexema);		
			return NUM;
		}
		printf("Saliendo totalmente...\n");		
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida...\n");
	else printf("cadena invalida \n");
	return 0;
}
