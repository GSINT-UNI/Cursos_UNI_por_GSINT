%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token START1 START2 IF ELSE PARI PARD ID FLECHA MAYOR MENOR NUM END 

%%
programa: START1 ID START2 expresion END ;
expresion:  ID FLECHA valor expresion| IF PARI condicion PARD expresion ELSE expresion | ;
valor: NUM | ID ;
condicion: valor signo valor ;
signo: MAYOR | MENOR ;


%%

//codigo, scanner, parser
void yyerror(char *mgs){
	printf("error: %s", mgs);
}
int yylex(){ //esto retorna un token es decir numeros 
//analizador lexico hecho a mano
	char c;
	char S[100];
	while(1){		
		c=getchar();;
		if(c=='\n') continue;
		if(isspace(c)) continue;
		if(c=='(') return PARI;		
		if(c==')') return PARD;
		if(c=='>') return MAYOR;
		if(c=='<') return MENOR;			
		if(c=='i') {
		     c=getchar();
		     if(c=='f') return IF;
	     }
		if(c=='e') {
		     c=getchar();
		     if(c=='l'){
		     c=getchar();
		     if(c=='s'){
		     c=getchar();
		     if(c=='e') return ELSE;
		     }
		     }
		}	
		if(c=='-') {
		     c=getchar();
		     if(c=='>') return FLECHA;	
		}
		
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
		     c=getchar();return START2;
		     }}}}}}}}}}}}}}
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
		     c=getchar();return END;
		     }}}}}}}}}}}}
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
	
			
