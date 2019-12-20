/*
----------------------------------
Inicio
x = -701 - 11*(105^11 - r(6011));
y = x^2 - (11-x);
Fin
---------------------------------
*/


%{
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char lexema[255];
void yyerror(char *);
int checkWord(char[]);
%}

%token ID OC PUNTCOM MAS MENOS POR ENTRE INIC FIN RAIZ POW
%%
raiz: INIC instruccion FIN;

instruccion: instruccion asignacion PUNTCOM| ;

asignacion: ID '=' oper | ID '=' MENOS oper;

oper: 	oper signo OC |	oper signo ID |	oper signo fact | oper signo RAIZ fact |	element;

fact: '(' oper ')';

element: 	OC | ID;

signo: 	MAS	| MENOS | ENTRE | POR | POW;
%%

void yyerror(char *msg){
	printf("error:%s", msg);
}



int yylex(){
	char c;
	while(1){
		c = getchar();
		if (c == '\n') continue;
		if (isspace(c)) continue;
		if (c == ';') return PUNTCOM;
		if (c == '+') return MAS;
		if (c == '-') return MENOS;
		if (c == '/') return ENTRE;
		if (c == '*') return POR;
		if (c == '^') return POW;


		if (isalpha(c)) {
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));

			ungetc(c, stdin);
			lexema[i] = 0;
	    if(strcasecmp(lexema,"Inicio")==0) return INIC;
	    if(strcasecmp(lexema,"Fin")==0) return FIN;
	    if(strcasecmp(lexema,"r")==0) return RAIZ;

	    return ID;
		}

		if (isdigit(c) && (c != '8') && (c != '9')){ 
			int decimalFlag = 0;
			int decimal_detectado = 0;
			int i = 0;
			do{
				if (decimalFlag){decimal_detectado = 1;}
				lexema[i++]=c;
				c=getchar();
				if( c == '.' ){decimalFlag = 1;}
			}while((isdigit(c) && (c != '8') && (c != '9') ) || (( c == '.' )&&(!decimal_detectado))); 

			ungetc(c, stdin);
			lexema[i] = 0;
			return OC;
		}
		return c;
	}
}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf("cadena invalida\n");
	return 0;
}
