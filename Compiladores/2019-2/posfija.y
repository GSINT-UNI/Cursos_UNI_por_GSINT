%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>

char lexema[64];
void yyerror(char *);
%}

%token ID NUM MAS MENOS MUL DIV  
%%

programa: estructura;

estructura: expresion estructura| ;

expresion: expresion expresion MAS|  expresion expresion MENOS| producto ;

producto:  expresion expresion MUL|  expresion expresion DIV| valor ;

valor: NUM | ID | '(' MENOS NUM ')';

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
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;
				
				
		if(isalpha(c)) {//verifica si es un caracter
			int i=0;
			do {
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			
         	ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return ID;//devuelve una palabra reservada
		}
		
		if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return NUM; //devuelve el token
		}
		
		return c;
	}
}

void main(){
//llamar al scaner o analizador lexico esto lo inicia el parser o analizador sintactico
//yyparse
	printf("Los numeros a operar deben estar separados en almenos un espacio\n");
	if(!yyparse())
		printf("cadena es valida\n");
	else
		printf("cadena invalida\n");
}
	
			
			
