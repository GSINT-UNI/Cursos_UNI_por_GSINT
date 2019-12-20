%{
#include <stdio.h>
#include <string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTOCOM MAS MENOS MUL DIV PUNTO
%%
programa: inicio cadena func fin;
inicio: cadena PUNTOCOM;
cadena: ID| cadena ID;
fin: cadena;
func: ecu | func ecu;	
ecu: ID IGUAL expr PUNTOCOM ;
expr: expr MAS expr1 | expr1 | expr MENOS expr1;
expr1: expr1 MUL expr2;
expr1: expr1 DIV expr2;
expr1: expr2;
expr1: expr2 '^' expr2;
expr2: '(' expr ')';
expr2: NUM | MENOS NUM | NUM PUNTO NUM | MENOS NUM PUNTO NUM | ID;
%%


void yyerror(char *mgs){
	printf("error: %s",mgs);
}

int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c==';') return PUNTOCOM;
		if(c=='=') return IGUAL;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;
		if(c=='.') return PUNTO;
		
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
		if(isdigit(c)){
			if(c!='0'){
				int i = 0;
				do{
					lexema[i++]=c;
					if(c<'8'){
						c=getchar();
					}
					else{
						c='a';
					}
				}while(isdigit(c));
				ungetc(c,stdin);
				lexema[i]== 0;
				return NUM;
			}
		}	
		return c;
}
}
int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf(" cadena invalida");
	return 0;
}
