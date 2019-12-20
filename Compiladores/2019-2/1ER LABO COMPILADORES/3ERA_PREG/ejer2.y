%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token	ID  NUM INICIO FIN IGUAL SIZQ SDER SI ELSE NOMBRE ORIGEN

//x:=4;
//en la zona de produccion %% ... %% no debe haber comentarios sino genera errores

%%

raiz:titulo INICIO'.' codigo FIN'.';
titulo: ORIGEN ID;
codigo: codigo declaracion |codigo enunciado | codigo negacion |;
declaracion: ID IGUAL NUM; 
enunciado: SI '('condicion')' declaracion;
negacion: ELSE declaracion;
condicion: ID SIZQ valor | ID SDER valor ;
valor: ID|NUM;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(){	//esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	int punto_detectado=0;
	int origen_detectado=0;
	int inicio_detectado=0;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c=='<') return SIZQ;
		if(c=='>') return SDER;
		if(c=='-'){
		    c=getchar();
		    if(c=='>') return IGUAL;
		};
		
		if(isalpha(c)){//verifique si es un caracter
		    //printf("Es cadena\n");
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();

			}while(isalnum(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;

		if (strcasecmp(lexema,"Algoritmo")==0) {origen_detectado=1;return ORIGEN;};
		if (strcasecmp(lexema,"if")==0) return SI;
	    if (strcasecmp(lexema,"else")==0) return ELSE;
		if (strcasecmp(lexema,"inicioAlgoritmo")==0){inicio_detectado=1; return INICIO;};
		if (strcasecmp(lexema,"finAlgoritmo")==0) return FIN;
        //if(origen_detectado==1 && inicio_detectado==0){printf("Nombre detectado...\n"); return NOMBRE;}
        //printf("Cadena");
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
