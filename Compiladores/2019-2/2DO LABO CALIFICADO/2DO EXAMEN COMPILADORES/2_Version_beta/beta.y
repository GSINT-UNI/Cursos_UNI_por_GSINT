%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>	
char lexema[64];
void yyerror(char *);
%}

%token PARI ID IGUAL NUM PUNTCOM MAS MENOS PARD MUL DIV POT START END RAIZ COM START1

%%
inicio: START1 ID PUNTCOM START recursion END;
recursion: recursion ID IGUAL expresion PUNTCOM | ;
expresion: expresion signo termino | termino ;
signo: MAS | MENOS;
termino: valor muldiv termino | valor ;
muldiv: MUL | DIV ;
valor: numero | ID | potencia| raiz | PARI expresion PARD;
potencia: valor POT numero ;
raiz : RAIZ PARI expresion PARD;
numero: signo NUM | NUM ;

%%

//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(){ //esto retorna un token es decir numeros 
//analizador lexico hecho a mano
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
		if(c=='^') return POT;
		

		if (isalpha(c)) {
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));

			ungetc(c, stdin);
			lexema[i] = 0;
		if(strcasecmp(lexema,"Programa")==0) return START1;
	    if(strcasecmp(lexema,"Inicio")==0) return START;
	    if(strcasecmp(lexema,"Fin")==0) return END;
	    if(strcasecmp(lexema,"r")==0) return RAIZ;
	    return ID;
		}

		if (isdigit(c) && (c != '8') && (c != '9')){ 
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while((isdigit(c) && (c != '8') && (c != '9') )); 

			ungetc(c, stdin);
			lexema[i] = 0;
			return NUM;
		}
		return c;
	}
}

void main(){
//llamar al scaner o analizador lexico esto lo inicia el parser o analizador sintactico
//yyparse

	if(!yyparse())
		printf("cadena es valida\n");
	else
		printf("cadena invalida\n");
}
	
			
