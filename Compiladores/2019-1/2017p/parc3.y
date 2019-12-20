%{
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token INICIO_PROGRAMA FIN_PROGRAMA INICIO_CLASE FIN_CLASE INICIO_METODO FIN_METODO EXTIENDE
%token ID PUNTOYCOMA PUNTO RETURN NUEVO COMA
%token MAS MENOS POR ENTRE POW IGUAL SENO COSENO
%token ABRE_PARENTESIS CIERRA_PARENTESIS
%token ENT DEC CHAR CAD BOOL REAL NUM
%token PROTEGIDO PRIVADO PUBLICO

%%


principal: primeralinea ;

primeralinea: permiso INICIO_CLASE ID restoclase FIN_CLASE
	| permiso INICIO_CLASE ID EXTIENDE ID restoclase FIN_CLASE;
	
	
restoclase: permiso asign PUNTOYCOMA restoclase RETURN func1 PUNTOYCOMA
	| permiso asign ABRE_PARENTESIS asign CIERRA_PARENTESIS contenido restoclase RETURN func1 PUNTOYCOMA
	| permiso asign ABRE_PARENTESIS CIERRA_PARENTESIS contenido restoclase RETURN func1 PUNTOYCOMA
	| ;

contenido: func1 contenido ;

func1: asign IGUAL func1
	| func1 MAS func2
	| func1 MENOS func2
	| func2;

func2: func2 POR func3
	| func2 ENTRE func3
	| func3;
	
func3: func3 POW func4
	| SENO ABRE_PARENTESIS func4 CIERRA_PARENTESIS
	| COSENO ABRE_PARENTESIS func4 CIERRA_PARENTESIS
	| func4;
	
func4: NUM
	| ID;
	
asign: ENT ID
	| CHAR ID
	| CAD ID
	| REAL ID
	| ID
	| asign COMA asign;
	
permiso: PROTEGIDO
	| PRIVADO
	| PUBLICO;
		

%%

int palabras_lenguaje( char lexema[] ) {
	if( strcmp( lexema, "programa" ) == 0 ) return INICIO_PROGRAMA;
	if( strcmp( lexema, "finprograma" ) == 0 ) return FIN_PROGRAMA;
	if( strcmp( lexema, "clase" ) == 0 ) return INICIO_CLASE;
	if( strcmp( lexema, "finclase" ) == 0 ) return FIN_CLASE;
	if( strcmp( lexema, "metodo" ) == 0 ) return INICIO_METODO;
	if( strcmp( lexema, "finmetodo" ) == 0 ) return FIN_METODO;
	if( strcmp( lexema, "retornar" ) == 0 ) return RETURN;
	if( strcmp( lexema, "extiende" ) == 0 ) return EXTIENDE;
	if( strcmp( lexema, "protegido" ) == 0 ) return PROTEGIDO;	
	if( strcmp( lexema, "privado" ) == 0 ) return PRIVADO;
	if( strcmp( lexema, "publico" ) == 0 ) return PUBLICO;
	if( strcmp( lexema, "nuevo" ) == 0 ) return NUEVO;
	if( strcmp(lexema, "entero")==0) return ENT;
	if( strcmp(lexema, "real")==0) return REAL;
	if( strcmp(lexema, "caracter")==0) return CHAR;
	if( strcmp(lexema, "cadena")==0) return CAD;
	if( strcmp(lexema, "booleano")==0) return BOOL;
	if( strcmp(lexema, "sen")==0) return SENO;
	if( strcmp(lexema, "cos")==0) return COSENO;	
	return ID;
}

void yyerror(char *mgs) {
	printf("error:%s",mgs);
}
int yylex() {
	char c;
	while(1) {
		c = getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c==';') return PUNTOYCOMA;
		if(c==',') return COMA;		
		if(c=='.') return PUNTO;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return POR;
		if(c=='/') return ENTRE;
		if(c=='^') return POW;		
		if(c=='(') return ABRE_PARENTESIS;
		if(c==')') return CIERRA_PARENTESIS;
		if(c=='=') return IGUAL;
		

		if(isalpha(c)) {//verifica si es un caracter
			int i=0;
			do {
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			
         ungetc(c,stdin);//devuelve el caracter a la entrada estandar
			lexema[i]=0;
			return palabras_lenguaje(lexema);//devuelve una palabra reservada
		}

		if(isdigit(c)) {//verifica si es un nro. entero
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			if (c=='.') {
				do{
					lexema[i++]=c;
					c=getchar();
				}while(isdigit(c));
			
            ungetc(c,stdin);
				lexema[i]=0;
				return DEC;//devuelve el TOKEN 
			}
			else {				
					ungetc(c,stdin);
					lexema[i]=0;
					return NUM;//devuelve el TOKEN 
			}
		}
		return c;
	}
}
//funcion principal
int main() {
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida \n");
	return 0;
}
