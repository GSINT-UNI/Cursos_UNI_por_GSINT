%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token PARI ID IGUAL NUM PUNTCOM MAS MENOS PARD MUL DIV COM POT START1 START2 END

%%
inicio: START1 ID PUNTCOM START2 recursion END;
recursion: recursion ID IGUAL expresion PUNTCOM | ;
expresion: expresion signo termino | termino ;
signo: MAS | MENOS;
termino: valor muldiv termino | valor | PARI expresion PARD;
muldiv: MUL | DIV ;
valor: numero | ID | potencia;
potencia: valor POT numero ;
numero: signo NUM COM NUM | NUM COM NUM | signo NUM | NUM ;


%%

//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(){ //esto retorna un token es decir numeros 
//analizador lexico hecho a mano
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c==';') return PUNTCOM;
		if(c==',') return COM;		
		if(c=='=') return IGUAL;
		if(c=='(') return PARI;		
		if(c==')') return PARD;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;
		if(c=='^') return POT;
		
		if(c=='P') {
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
		     c=getchar();
		     if(c=='a'){
		     c=getchar();return START1;
		     }}}}}}}
		}
		
		if(c=='I') {
		     c=getchar();
		     if(c=='n'){
		     c=getchar();
               if(c=='i'){
		     c=getchar();
		     if(c=='c'){
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();return START2;
		     }}}}}
		}
		
		if(c=='F') {
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
               if(c=='n'){
		     c=getchar();return END;
		     }}
		}
		
		if(isalpha(c)){//verifica si es un caracter
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return ID; //devuelve el token
		}
		if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return NUM; //devuelve el token
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
	
			
