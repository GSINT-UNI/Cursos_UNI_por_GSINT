%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#define YYSTYPE double  /*double type for YACC stack */
char lexema[64];
void yyerror(char *);
%}

%token NUM RAIZ POT
%%
prog: expresion prog  {printf("VALOR %g \n", $1); };
prog: ;

expresion: expresion '+' termino { $$ = $1 + $3; }
		| expresion '-' termino { $$ = $1 - $3; }
		| termino 
		;
termino: termino '*' valor { $$ = $1 * $3; }
		| termino '/' valor { $$ = $1 / $3; }
		| valor 
		;
valor: NUM 
		| '(' expresion ')' { $$ = ($2); }
        |raiz
        |potencia
        
raiz: RAIZ '(' expresion ')'{$$ = sqrt($3);};
potencia:  POT'('expresion','expresion')' {$$ = pow($3,$5);};

%%

//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(void){ //esto retorna un token es decir numeros 
//analizador lexico hecho a mano
	double t;
	int c;
	while( (c = getchar() ) == ' ');
    if (isalpha(c)) {
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));

			ungetc(c, stdin);
			lexema[i] = 0;
	    if(strcasecmp(lexema,"r")==0) return RAIZ;
	    if(strcasecmp(lexema,"pow")==0) return POT;
		}
	if(isdigit(c)){//verifica si es un nro. entero
		ungetc(c, stdin);
		scanf("%lf",&t); 
		yylval=t; //pasa valor a la pila
		return NUM; //devuelve el token
	}
	return c;
	
}

int main(void){

	return yyparse();

}
			
