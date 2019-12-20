%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token	NUM  

prod: TEXTO '@' TEXTO '.' DOMINIO
//x:=4;
//en la zona de produccion %% ... %% no debe haber comentarios sino genera errores

%%
expresion: expresion val |;
val: NUM|'-'NUM;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(){	//esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	int decimal_detected=0;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		
		if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
				if(c=='.'){
					decimal_detected++;
				}
			}while(isdigit(c) || (c=='.' && decimal_detected<2));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return NUM; // devuelve el token
		}
		return c;
	}
}
void main(){
//llamar al scaner o analizador lexico esto lo inicia el parser o analizador sintactico(yyparse)
//yyparse

	if(!yyparse())
		printf("cadena es valida\n");
	else
		printf("cadena invalida\n");
}
