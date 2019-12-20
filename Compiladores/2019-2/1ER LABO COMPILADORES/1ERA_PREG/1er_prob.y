%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token	CONTRA  

//x:=4;
//en la zona de produccion %% ... %% no debe haber comentarios sino genera errores

%%
expresion: CONTRA;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(){	//esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	int out_of_lyric=0;

	while(1){
		c=getchar();
		if(c=='\n') continue;

		if(isalnum(c)){//verifica si es un nro. entero
			int i=0;
			if(c<'A' || c>'F'){
				out_of_lyric == 1;
			}
			do{
				lexema[i++]=c;
				c=getchar();
		if(c<'A' || c>'F'){
			out_of_lyric == 1;
			}
			}while(isalnum(c));
		if(out_of_lyric == 0){
		
			ungetc(c,stdin);//devuelve el caracter a la entrada estandar
			lexema[i]=0;
			return CONTRA; // devuelve el token
		}
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