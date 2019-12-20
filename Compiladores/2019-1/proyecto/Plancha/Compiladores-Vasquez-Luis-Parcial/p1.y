/*
Examen Parcial - Compiladores
Alumno: Vasquez Espinoza, Luis
Preg. 1
*/

%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTCOM
%%
instruccion: instruccion compx ';'| ;
compx: '(' num ',' num ')';
num: NUM | '-' NUM;
%%

void yyerror(char *msg){
	printf("error:%s", msg);
}

int yylex(){
	char c;
	while(1){
		c = getchar();
		if (c == '\n') continue;
		if (isspace(c)) continue;
		
		if (isdigit(c)){
			int decimalFlag = 0;
			int decimalReaded = 0;
			int i = 0;
			do{
				if (decimalFlag){decimalReaded = 1;}
				lexema[i++]=c;
				c=getchar();
				if( c == '.' || c == 'e' || c == 'E' ){decimalFlag = 1;}
			}while((isdigit(c)) || (( c == '.' || c == 'e' || c == 'E' )&&(!decimalReaded)));

			ungetc(c, stdin);
			lexema[i] = 0;
			return NUM;
		}
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida\n");
	return 0;
}
