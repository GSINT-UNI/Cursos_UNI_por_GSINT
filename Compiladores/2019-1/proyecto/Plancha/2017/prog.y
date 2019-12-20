%{
#include <stdio.h>
#include <string.h>
char lexema[1005];
void yyerror(char *);
%}

%token ID NUM EXPRESION PRINCIPAL SI SINO SEGUN CASO OTROCASO PARA MIENTRAS HACER ENTERO REAL CARACTER CADENA BOOLEANO LEER IMPRIMIR

%%
S: PRINCIPAL '('')''{' listaInstr '}';

listaInstr: listaInstr asignacion | listaInstr operacion | listaInstr lectura | listaInstr impresion | listaInstr condicional | listaInstr seguncaso | listaInstr bucle1 | listaInstr bucle2 | listaInstr bucle3 | asignacion | operacion | lectura | impresion | condicional | seguncaso | bucle1 | bucle2 | bucle3;

asignacion: variable ID ';'| variable ID '=' oper1 ';';

operacion: ID '=' oper1 ';' | ID'+''+' | ID'-''-';
oper1: oper2'+'oper1 | oper2'-'oper1 | oper2;
oper2: oper3'*'oper2 | oper3'/'oper2 | oper3;
oper3: term'^'oper3 | term;
term: NUM | ID | '('oper1')';

//VARIABLES
variable: ENTERO | REAL | CARACTER | CADENA | BOOLEANO;

//Lectura
lectura: LEER '>''>' lectura2 ';'
lectura2: ID | lectura2 '>''>' ID;

//Impresion
impresion: IMPRIMIR '<''<' impresion2 ';' | IMPRIMIR '<''<' impresion2 '<''<' '"' '\n' '"' ';' | IMPRIMIR '<''<' '"' '\n' '"' ';';
impresion2: term2 | term2 '<''<' impresion2;
term2: NUM | ID | EXPRESION;

//CONDICIONALES
condicional:  SI '('condicion')' '{'listaInstr'}' | SI '('condicion')' '{'listaInstr'}' condicional2 | SI '('condicion')' '{'listaInstr'}' condicional2 SINO '{'listaInstr'}' |  SI '('condicion')' '{'listaInstr'}' SINO '{'listaInstr'}';
condicional2: condicional2 SINO SI '('condicion')' '{'listaInstr'}' | SINO SI '('condicion')' '{'listaInstr'}'; 
condicion: condicion operlogico oper1 signocomparacion oper1 | oper1 signocomparacion oper1;
signocomparacion: '=''=' | '!''=' | '>' | '<' | '>''=' | '<''=';
operlogico: '&''&' | '|''|';

//SEGUN
seguncaso: SEGUN '('ID')' '{'casos'}';
casos: CASO NUM ':' listaInstr | CASO NUM ':' listaInstr casos2 | CASO NUM ':' listaInstr casos2 OTROCASO ':' listaInstr; 
casos2: CASO NUM ':' listaInstr | CASO NUM ':' listaInstr casos2

//BUCLE1
bucle1: PARA '('inicializacion';'condicion';'actualizacion ')' '{'listaInstr'}';
inicializacion: variable ID '=' oper1 ',' inicializacion | variable ID '=' oper1 | ID '=' oper1 ',' inicializacion | ID '=' oper1;
actualizacion: ID '=' oper1 ',' actualizacion | ID '=' oper1 | ID '+''+' | ID '-''-' | ID '+''+' ',' actualizacion | ID '-''-'',' actualizacion;

//BUCLE2
bucle2: MIENTRAS '('condicion')' '{'listaInstr'}';

//BUCLE3
bucle3: HACER '{'listaInstr'}' MIENTRAS '('condicion')' ';';

%%

void yyerror(char *mgs)
{
	printf("error: %s\n",mgs);
}

int EsPalabraReservada(char lexema[])
{
	if(strcasecmp(lexema, "principal")==0) return PRINCIPAL;
	if(strcasecmp(lexema, "entero")==0) return ENTERO;
	if(strcasecmp(lexema, "real")==0) return REAL;
	if(strcasecmp(lexema, "caracter")==0) return CARACTER;
	if(strcasecmp(lexema, "cadena")==0) return CADENA;
	if(strcasecmp(lexema, "booleano")==0) return BOOLEANO;
	if(strcasecmp(lexema, "leer")==0) return LEER;
	if(strcasecmp(lexema, "imprimir")==0) return IMPRIMIR;
	if(strcasecmp(lexema, "si")==0) return SI;
	if(strcasecmp(lexema, "sino")==0) return SINO;
	if(strcasecmp(lexema, "para")==0) return PARA;
	if(strcasecmp(lexema, "mientras")==0) return MIENTRAS;
	if(strcasecmp(lexema, "hacer")==0) return HACER;
	if(strcasecmp(lexema, "segun")==0) return SEGUN;
	if(strcasecmp(lexema, "caso")==0) return CASO;
	if(strcasecmp(lexema, "otrocaso")==0) return OTROCASO;
	return ID;
}

int linea = 1;

int yylex()
{
	char c;
	int i;
	while(1)
	{
		c=getchar();
		if(c==' ') continue;
		if(c=='\t') continue;
		if(c=='\n') {linea++; continue;}
		if(isdigit(c))
		{
			i=0;
			do
			{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c,stdin);
			lexema[i]=0;
			return NUM;
		}
		if(isalpha(c))
		{
			i=0;
			do
			{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]=0;
			return EsPalabraReservada(lexema);
		}
		if(c=='"')
		{
			i=0;
			do
			{
				if(i>1000) return c;
				lexema[i++]=c;
				c=getchar();
			}while(c!='"');
			lexema[i]=0;
			return EXPRESION;
		}
		return c;
	}
}


int main()
{
	if(!yyparse()) printf("la cadena es valida\n");
	else printf("la cadena es invalida en la línea %d\n",linea);
}





