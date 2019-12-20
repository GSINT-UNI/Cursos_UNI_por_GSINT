/*
Examen Parcial - Compiladores
Alumno: Vasquez Espinoza, Luis
Preg. 3
*/
%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
#define YYSTYPE double /*double type for YACC stack*/
%}

%token PRG INI FIN ID NUM PUNTCOM NEW LIB H VAR TYPE MAS MENOS ENTRE POR SEN RAIZ
%%
raiz: PRG ID cabeceras inics INI instruccion FIN;

cabeceras:	cabecera cabeceras
		|	cabecera;
		
cabecera: LIB '<'ID'>';

instruccion: 	instruccion asignacion
			|	instruccion cabecera
			|	instruccion inic
			|	/*vacio*/;

asignacion: ID '=' oper;

inics: 	inic inics
	|	inic;

inic:	VAR idlist':'TYPE

idlist: 	ID',' idlist
		|	ID;

asignacion:	ID '=' oper '\n';// {printf("num:%g\n", $3);};

oper: 	oper '+' element
	|	oper '-' element
	|	oper '/' element
	|	oper '*' element
	|	oper '^' element
	|	oper RAIZ '(' element ')'
	|	oper SEN '(' element ')'
	
	|	oper '+' fact
	|	oper '-' fact
	|	oper '/' fact
	|	oper '*' fact
	|	oper RAIZ '('fact')'
	|	oper SEN '('fact')'
	
	|	fact
	|	element;
	
fact: '('oper')';

element: 	NUM
		|	'-' NUM
		|	ID;

%%

void yyerror(char *msg){
	printf("error:%s", msg);
}

int reservedWord(char lexema[])
{
	if(strcasecmp(lexema,"Program")==0) return PRG;
	if(strcasecmp(lexema,"Inicio")==0) return INI;
	if(strcasecmp(lexema,"Fin")==0) return FIN;
	if(strcasecmp(lexema,"new")==0) return NEW;
	if(strcasecmp(lexema,"#libreria")==0) return LIB;
	if(strcasecmp(lexema,".h")==0) return H;
	if(strcasecmp(lexema,"Var")==0) return VAR;
	if(strcasecmp(lexema,"real")==0) return TYPE;
	if(strcasecmp(lexema,"sen")==0) return SEN;
	if(strcasecmp(lexema,"raiz")==0) return RAIZ;
	return ID;
}

int yylex(){
	char c;
	while(1){
		c = getchar();
		if (isspace(c)) continue;

		if(c == '.' || isdigit(c)){
			ungetc(c, stdin);
			scanf("%lf", &yylval);
			return NUM;
		}
		
		if (isalpha(c) || c == '.' || c == '#') {
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c) || c == '.' || c == '#');

			ungetc(c, stdin);
			lexema[i] = 0;
			return reservedWord(lexema);
		}
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida\n");
	return 0;
}
