%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token	ID  NUM PUNTCOM INICIO FIN

//x:=4;
//en la zona de produccion %% ... %% no debe haber comentarios sino genera errores

%%
raiz:INICIO expresion FIN;
expresion: expresion ID ':''=' termino PUNTCOM;
expresion: ;
termino: termino '+' factor |factor;
factor: NUM|ID|'-'NUM;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(){	//esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c==';') return PUNTCOM;
		
		if(isalpha(c)){//verifique si es un caracter
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		if (strcasecmp(lexema,"INICIO")==0) return INICIO;
		if (strcasecmp(lexema,"FIN")==0) return FIN;
		return ID; // devuelve el token
		}
		if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
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
