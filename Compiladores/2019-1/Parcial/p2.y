%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token INICIO FINAL HEREDAR MAIN PRIVADO PUBLICO PROTEGIDO PUNTCOM ID NUM IGUAL NUEVO INT FLOAT LONG CHAR STRING BOOL RETURN;

%%

programa: INICIO creacion_clase metodo_main FINAL;

permiso: PUBLICO | PRIVADO | PROTEGIDO ;

creacion_clase: creacion_clase permiso ID '{' clase_estructura '}' | creacion_clase permiso ID HEREDAR ID'{' clase_estructura '}' | ;

clase_estructura: clase_estructura atributos | clase_estructura metodo | ;

atributos: permiso declarar ;

metodo: permiso tipo ID '(' parametros ')' '{' estructura_metodo '}' RETURN ID PUNTCOM ; 

parametros: tipo ID ',' parametros | tipo ID ;

estructura_metodo: estructura_metodo declarar | estructura_metodo crear_objeto | estructura_metodo crear_metodo_objeto | ; 

tipo: INT | CHAR | STRING | BOOL | LONG | FLOAT ;

crear_objeto: tipo ID IGUAL NUEVO ID '(' parametros_objeto ')' PUNTCOM ;

crear_metodo_objeto: ID '.' ID '(' parametros_objeto ')' ;

parametros_objeto: valor ',' parametros_objeto | valor | ;

metodo_main: permiso tipo MAIN '(' parametros ')' '{' estructura_metodo '}' RETURN ID PUNTCOM;

valor: ID | NUM | ID '.' ID;

declarar: declarar tipo ID IGUAL valor PUNTCOM | declarar tipo ID PUNTCOM  | ',' ; 
%% 

int palabras( char lexema[] ) {
	if( strcmp( lexema, "INICIO" ) == 0 ) return INICIO;
	if( strcmp( lexema, "FINAL" ) == 0 ) return FINAL;	
	if( strcmp( lexema, "heredar" ) == 0 ) return HEREDAR;
	if( strcmp( lexema, "main" ) == 0 ) return MAIN;
	if( strcmp( lexema, "publico" ) == 0 ) return PUBLICO;
	if( strcmp( lexema, "privado" ) == 0 ) return PRIVADO;
	if( strcmp( lexema, "protegido" ) == 0 ) return PROTEGIDO;
	if( strcmp( lexema, "int" ) == 0 ) return INT;
	if( strcmp( lexema, "float" ) == 0 ) return FLOAT;	
	if( strcmp( lexema, "char" ) == 0 ) return CHAR;
	if( strcmp( lexema, "string" ) == 0 ) return STRING;
	if( strcmp( lexema, "bool" ) == 0 ) return BOOL;
	if( strcmp( lexema, "long" ) == 0 ) return LONG;
	if( strcmp( lexema, "return" ) == 0 ) return RETURN;
	if( strcmp( lexema, "nuevo" ) == 0 ) return NUEVO;
	return ID;
}



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
		//if(c=='+') return MAS;
		//if(c=='-') return MENOS;
		//if(c=='*') return MUL;
		//if(c=='/') return DIV;	
				
		if(isalpha(c)) {
			int i=0;
			do {
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			
         	ungetc(c,stdin);
		lexema[i]=0;
		return palabras(lexema);
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
	
			
			
