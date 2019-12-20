%{
#include <stdio.h>
#include <string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTCOM MAS MENOS MULT DIV POW RAIZ MENOR MAYOR IGIG DIF BEGIN END 

%%

cuerpo: BEGIN fuente END;

fuente: sentencia_if fuente
	| sentencia_while fuente  
	| sentencia_for fuente  	
	| funcion fuente
	| asignacion fuente
	|
	;

funcion: '(' '"' ID '"'  lista_ID')' '[' funcion_cuerpo ']';

funcion_cuerpo: lista_expr  ;


lista_expr: asignacion lista_expr
	| sentencia_if lista_expr
	| sentencia_while lista_expr
	| sentencia_for lista_expr	
	| 
	;

sentencia_if: '?' '(' lista_cond ')' '[' lista_expr ']';

sentencia_while: '#' '(' lista_cond ')' '[' lista_expr ']';

sentencia_for: '%' '(' asignacion condicion2 PUNTCOM cont ')' '[' lista_expr ']';

lista_cond: condicion lista_cond
	| condicion '&' lista_cond
	| condicion '|' lista_cond
	|
	;
condicion: MENOR expr expr
	| MAYOR expr expr
	| IGIG expr expr
	| DIF expr expr
	;

condicion2: MENOR expr expr
	| MAYOR expr expr
	| MAYOR IGIG expr expr
	| MENOR IGIG expr expr
	;
	
cont: MAS expr expr
	| MENOS expr expr
	;

lista_ID:
	| ID lista_ID
	;

asignacion: IGUAL ID instruccion;

instruccion: expr PUNTCOM;

expr: MAS expr term 
	| term
	| MENOS expr term
	;

term: form
	| MULT term form 
	| DIV term form
	;

form: form2
	| RAIZ '(' form3 ')'
	| POW form form2
	;
	
form2: '(' expr ')'
	| NUM
	| '(' MENOS NUM ')'
	| ID
	;
	
form3: NUM
	| ID
	;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error:%s",mgs);
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
		if(c=='+') return MAS;
		if(c=='*') return MULT;
		if(c=='/') return DIV;
		if(c=='@') return RAIZ;
		if(c=='^') return POW;		
		if(c=='-') return MENOS;
		if (c=='<') return MENOR;
		if (c=='>') return MAYOR;
		if(c==':') return IGIG;
		if(c=='!') return DIF;
		
		if(c=='B'){
			c=getchar();
			if(c=='e'){
				c=getchar();
				if(c=='g'){
					c=getchar();
					if(c=='i'){
						c=getchar();
						if(c=='n'){
							return BEGIN;					
						}
					}
				}
				
			}
			
		}
		if(c=='E'){
			c=getchar();
			if(c=='n'){
				c=getchar();
				if(c=='d'){
					return END;					
							
				}
				
			}
			
		}

		if(isalpha(c)){ 
		//if(isalnum(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
		
			ungetc(c,stdin);
			lexema[i]=0;
			return ID;
		}

		if(isdigit(c)){
		        int i=0;
     		        do{
                		lexema[i++]=c;
                		c=getchar();
            		}while(isdigit(c));
            		ungetc(c,stdin);
            		lexema[i]=0;
            		return NUM;
		}

		return c;		
	}//fin_while
}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida \n");
	return 0;
}
