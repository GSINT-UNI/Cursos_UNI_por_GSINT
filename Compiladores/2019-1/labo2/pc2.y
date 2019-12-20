%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token  ID IGUAL NUM PUNTCOM MAS MENOS MUL DIV COM START1 START2 END FIZQ FDER RAIZ SI ENTONCES INICIO FIN PARI PARD

%%
inicio: START1 FIZQ ID FDER START2 declaracion enunciado END ;
declaracion: ID IGUAL valor COM declaracion | ;
enunciado: ID IGUAL operacion PUNTCOM enunciado | SI condicion ENTONCES INICIO enunciado FIN  | ;
operacion: muldiv |  muldiv signo operacion ;
muldiv:  valor md muldiv | valor ;
condicion: ID FIZQ valor | ID FDER valor ;
raiz: RAIZ PARI operacion PARD;
md: MUL | DIV;
valor: NUM | ID | raiz;
signo: MAS | MENOS;
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
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MUL;
		if(c=='/') return DIV;
		if(c=='(') return PARI;		
		if(c==')') return PARD;
		if(c=='<') return FIZQ;
		if(c=='>') return FDER;		
		if(c==',') return COM ;
		if(c=='S') {
		     c=getchar();
		     if(c=='i') return SI;}
		     
		if(c=='e') {
		     c=getchar();
		     if(c=='n'){
		     c=getchar();
         if(c=='t'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();
		     if(c=='n'){
		     c=getchar();
		     if(c=='c'){
		     c=getchar();
		     if(c=='e'){
		     c=getchar();
		     if(c=='s') return ENTONCES;}}}}}}}
		     
		if(c=='A') {
		     c=getchar();
		     if(c=='l'){
		     c=getchar();
         if(c=='g'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();
		     if(c=='r'){
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
		     if(c=='t'){
		     c=getchar();
		     if(c=='m'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();return START1;
		     }}}}}}}}
		}
		
		if(c=='i') {
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
		     c=getchar();
		     if(c=='A'){
		     c=getchar();
		     if(c=='l'){
		     c=getchar();
         if(c=='g'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();
		     if(c=='r'){
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
		     if(c=='t'){
		     c=getchar();
		     if(c=='m'){
		     c=getchar();
		     if(c=='o')return START2;
		     }}}}}}}}}}}}}
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
		     if(c=='o') return INICIO;}}}}}
		
		
		if(c=='F') {
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
         if(c=='n') return FIN;
		     }
		}
		
		if(c=='f') {
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
         if(c=='n'){
		     c=getchar();		     
		     if(c=='A'){
		     c=getchar();
		     if(c=='l'){
		     c=getchar();
         if(c=='g'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();
		     if(c=='r'){
		     c=getchar();
		     if(c=='i'){
		     c=getchar();
		     if(c=='t'){
		     c=getchar();
		     if(c=='m'){
		     c=getchar();
		     if(c=='o'){
		     c=getchar();
		     if(c=='.'){
		     c=getchar(); return END;
		     }}}}}}}}}}}}
		}		
		
		if(c=='r') {
		     c=getchar();
		     if(c=='a'){
		     c=getchar();
         if(c=='i'){
		     c=getchar();
		     if(c=='z') return RAIZ;
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
	
			
