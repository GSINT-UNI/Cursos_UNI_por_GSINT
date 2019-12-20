%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char lexema[64];
void yyerror(char *);
%}

%token PARI IGUAL NUM PUNTCOM MAS MENOS PARD MUL DIV

%%
recursion: recursion expresion PUNTCOM | ;
expresion: expresion signo termino | termino ;
signo: MAS | MENOS;
termino: valor muldiv termino | valor ;
muldiv: MUL | DIV ;
valor: numero | PARI expresion PARD;
numero: signo NUM | NUM ;

%%


void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(){ 

	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c==';') return PUNTCOM;
		if(c=='=') return IGUAL;
		if(c=='(') return PARI;		
		if(c==')') return PARD;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;

		if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			int decimalFlag = 0;
			int decimal_detectado=0;
			do{
			    if (decimalFlag){decimal_detectado = 1;}
				lexema[i++]=c;
				c=getchar();
				if( c == ',' ){decimalFlag = 1;}
			}while(isdigit(c) || (( c == ',' )&&(!decimal_detectado)) );
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return NUM; //devuelve el token
		}
		return c;
	}
}

void main(){


	if(!yyparse())
		printf("cadena es valida\n");
	else
		printf("cadena invalida\n");
}
	
			
