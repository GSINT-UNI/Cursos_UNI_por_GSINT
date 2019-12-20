%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID NUM MAS MENOS MUL DIV PUNTOCOM
%%
expresion: expr1 MUL expr2 PUNTOCOM | expr1 DIV expr2 PUNTOCOM;
expr1: expr MAS expr | expr MENOS expr;
expr2: '(' expr3 ')';
expr3: expr4 MAS expr | expr4 MENOS expr;
expr4: expr DIV expr | expr MUL expr | expr;
expr: NUM | MENOS NUM'.'NUM | NUM'.'NUM;

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
