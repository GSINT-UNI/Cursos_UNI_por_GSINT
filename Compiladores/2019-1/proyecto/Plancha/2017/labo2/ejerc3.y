%{
#include <stdio.h>
#include <string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID NUM MAS MENOS MUL DIV PUNTOCOM PUNTO
%%
expresion: expr PUNTOCOM ;
expr: expr MAS expr1 | expr1 | expr MENOS expr1;
expr1: expr1 MUL expr2;
expr1: expr1 DIV expr2;
expr1: expr2;
expr2: '(' expr ')';
expr: NUM | MENOS NUM | MENOS NUM PUNTO NUM | NUM PUNTO NUM;

%%
//codigo ,scanner, parser
void yyerror(char *mgs){
	printf("error:%s",mgs);
}

int yylex(){  //esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;
		if(c==';') return PUNTOCOM;
		if(c=='.') return PUNTO;		
		
		if(isalpha(c)){//verifica si es un caracter
			int i = 0;
			do{

			lexema[i++]=c;
			c=getchar();

			}while(isalnum(c));

			ungetc(c,stdin);
			lexema[i]== 0;
			return ID;
		}
		if(isdigit(c)){
			int i = 0;

			do{

			lexema[i++]=c;
			c=getchar();

			}while(isdigit(c));

			ungetc(c,stdin);
			lexema[i]== 0;
			return NUM;
		}	
		return c;
	}

}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf(" cadena invalida \n");
	return 0;
}
