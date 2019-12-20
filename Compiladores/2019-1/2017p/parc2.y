%{
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token INICIO_PROGRAMA FIN_PROGRAMA INICIO_CLASE FIN_CLASE INICIO_METODO FIN_METODO EXTIENDE
%token ID PUNTOYCOMA PUNTO RETURN NUEVO COMA
%token MAS MENOS POR ENTRE IGUAL
%token ABRE_PARENTESIS CIERRA_PARENTESIS
%token ENT DEC CHAR CAD BOOL REAL NUM
%token PROTEGIDO PRIVADO PUBLICO

%%
main: INICIO_PROGRAMA primera_linea_clase primera_linea_metodo_main FIN_PROGRAMA;

primera_linea_clase: permiso INICIO_CLASE ID  resto_clase FIN_CLASE primera_linea_clase
	| permiso INICIO_CLASE ID EXTIENDE ID resto_clase FIN_CLASE primera_linea_clase
	| ;

resto_clase: atributo resto_clase
	| primera_linea_metodo resto_clase
	| ;

atributo: permiso ID IGUAL nivel1 PUNTOYCOMA
	| permiso ID PUNTOYCOMA
	| permiso asignacion PUNTOYCOMA;

primera_linea_metodo: permiso INICIO_METODO asignacion ABRE_PARENTESIS declaracion CIERRA_PARENTESIS  contenido FIN_METODO
   | permiso INICIO_METODO asignacion ABRE_PARENTESIS CIERRA_PARENTESIS  contenido FIN_METODO
   | permiso INICIO_METODO asignacion ABRE_PARENTESIS declaracion CIERRA_PARENTESIS  contenido RETURN nivel1 PUNTOYCOMA FIN_METODO
   | permiso INICIO_METODO asignacion ABRE_PARENTESIS CIERRA_PARENTESIS  contenido RETURN nivel1 PUNTOYCOMA FIN_METODO;

primera_linea_metodo_main: primera_linea_metodo primera_linea_metodo_main
	| ;

declaracion: ID
   | ID PUNTOYCOMA declaracion 
   | asignacion 
   | asignacion COMA declaracion;

contenido: var PUNTOYCOMA contenido
	| contenido_metodo_main contenido
	| contenido_objeto contenido
	| contenido_metodo_objeto contenido
   | ;

contenido_objeto: ID IGUAL NUEVO ID ABRE_PARENTESIS parametros_bloq CIERRA_PARENTESIS PUNTOYCOMA
	| ID IGUAL NUEVO ID ABRE_PARENTESIS CIERRA_PARENTESIS PUNTOYCOMA;

contenido_metodo_objeto: ID PUNTO ID ABRE_PARENTESIS parametros_bloq CIERRA_PARENTESIS PUNTOYCOMA
   | ID PUNTO ID ABRE_PARENTESIS CIERRA_PARENTESIS PUNTOYCOMA
   | ID IGUAL ID PUNTO ID ABRE_PARENTESIS parametros_bloq CIERRA_PARENTESIS PUNTOYCOMA
   | ID IGUAL ID PUNTO ID ABRE_PARENTESIS CIERRA_PARENTESIS PUNTOYCOMA;

contenido_metodo_main: ID ABRE_PARENTESIS parametros_bloq CIERRA_PARENTESIS PUNTOYCOMA
   | ID ABRE_PARENTESIS CIERRA_PARENTESIS PUNTOYCOMA
   | ID IGUAL ID ABRE_PARENTESIS parametros_bloq CIERRA_PARENTESIS PUNTOYCOMA
   | ID IGUAL ID ABRE_PARENTESIS CIERRA_PARENTESIS PUNTOYCOMA;

parametros_bloq: term
   | term PUNTOYCOMA parametros_bloq;

var: ID IGUAL nivel1
	| ID PUNTO ID IGUAL nivel1;

nivel1: nivel2 ABRE_PARENTESIS nivel1 CIERRA_PARENTESIS nivel2
   | nivel2 '\n' nivel1 { printf("VALOR %g\n",$1); };
   | ;

nivel2: nivel2 MAS nivel3 { $$ = $1 +$3; }
   | nivel2 MENOS nivel3  { $$ = $1 - $3; }
   | nivel3;
 
nivel3: nivel3 POR nivel4 { $$ = $1 * $3; }
   | nivel3 ENTRE nivel4  { $$ = $1 / $3; }
   | nivel4;

nivel4: nivel4 IGUAL term
   | term;
   
asignacion: ENT ID
	| REAL
	| ID
	| CHAR ID
	| CAD ID
	| asignacion COMA asignacion;

term: NUM
   | DEC
   | CHAR
   | CAD
   | ID
   | ID PUNTO ID
   | ;

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
		if(c==',') return PUNTOYCOMA;		
		if(c=='.') return PUNTO;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return POR;
		if(c=='/') return ENTRE;
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
