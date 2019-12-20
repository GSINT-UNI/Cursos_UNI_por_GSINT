%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token CONTRASENA COMPLEJO

%%
pass: CONTRASENA | COMPLEJO;
%%

//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(){ //esto retorna un token es decir numeros 
//analizador lexico hecho a mano
	char c;
	int n,a;
	n=0;
	a=0;
	int i=0;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;	
			
		if(isupper(c)) {
		  do{
		    i++;
		    c=getchar();
		    if(isdigit(c))
		      n++;
		    if(isalnum(c))
		      a++; 
		    //if(i==5) break;	   
		  }while(i<5 );
		if(n==2 && a ==2 ) return CONTRASENA;   
		}
		
		/*if(c=='('){
		  c=getchar();
		  if(c=='+' || c=='-'){
		    c=getchar();
		    if(isdigit(c)){
		      c=getchar();
		      if(c=='.'){
		        c=getchar();
		        if(isdigit(c)){
		          c=getchar();
		          if(c==','){
		            c=getchar();  
		            if(c=='+' || c=='-'){
		             c=getchar();
		              if(isdigit(c)){
		               c=getchar();
		               if(c=='.'){
		                 c=getchar();
		                 if(isdigit(c)){
		                   c=getchar();
		                   if(c==')') return COMPLEJO;
		                 }}}}} 
		          }
		        }
		      }
		  }
		  if(isdigit(c)){
		  
		  }  
		}*/
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
	
			
