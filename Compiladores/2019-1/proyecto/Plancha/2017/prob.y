%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token  ID IGUAL NUM PUNTCOM MAS MENOS RAIZ SENO BEGIN END PROGRAM VAL


//produccion  x:=4
//en la zona de produccion %%  ... %% no debe haber comentarios sino genera errores
//intr: ID ':' IGUAL NUM '\n';
//listaInstr es el estado inicial
%%

fuente : PROGRAM ID lista_var
	| 
	;
	
lista_var: VAL ID lista_ID cuerpo
	;

lista_ID: 
	| ID lista_ID
	;

cuerpo: BEGIN lista_instr END;
	
	
lista_instr: instr lista_instr
	|
	;
	
instr: ID ':' IGUAL expr PUNTCOM;
expr:expr MAS term 
	| term 
	| expr MENOS term
	;
	
term: form
	| term '*' form
	| term '/' form
	;

form: '(' expr ')'
	| NUM
	| ID
	| MENOS form
	| SENO '(' expr ')'
	| RAIZ '(' expr ')'
	;
%%
//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(){   //esto retorna un token es decir numeros
//analizador lexico hecho a mano
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c=='\t') continue;
	 	if(c==';') return PUNTCOM;
		if(c=='=') return IGUAL;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='?') return RAIZ;
		if(c=='#') return SENO;
		if(c=='P'){
			c=getchar();
			if(c=='r'){
				c=getchar();
				if(c=='o'){
					c=getchar();
					if(c=='g'){
						c=getchar();
						if(c=='r'){
							c=getchar();
							if(c=='a'){
								c=getchar();
								if(c=='m'){
									return PROGRAM;
								}
							}
						}
					}
				}
				
			}
			
		}
		
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
		
		if(c=='V'){
			c=getchar();
			if(c=='a'){
				c=getchar();
				if(c=='l'){
					return VAL;					
							
				}
				
			}
			
		}
 		if(isalpha(c)){//verifica si es un caracter
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
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

