%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token DNI CODIGO NOMBRE NUMEROS

//definicion lexica

//DNI [0-9]{8}
//CODIGO (0[A-Z]*[0]*[1]*{6})
//NOMBRE [a-z|0-9]*{100}
//NUMEROS [0-9]*[' ']

%%
instruccion: instruccion  DNI ;
instruccion: instruccion  CODIGO ;
instruccion: instruccion  NOMBRE ; 
instruccion: instruccion  NUMEROS ;
instruccion: ;
%%

void yyerror(char *mgs){
	printf("error:%s",mgs);
}
int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		
		//definicion por funciones
		
		if(isdigit(c)){
			int i = 0;
			do{
			lexema[i++]=c;
			c=getchar();

			}while(isdigit(c));

			ungetc(c,stdin);
			lexema[i]== 0;
			if(i==8) return DNI;
		}	

		if(isalpha(c) || isdigit(c)){
			int i = 0;
			do{
			lexema[i++]=c;
			c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]== 0;
			if(i<100) return NOMBRE;
		}

		if(isdigit(c)){
			int i = 0;
			do{
			lexema[i++]=c;
			c=getchar();
			}while(isdigit(c));
			ungetc(c,stdin);
			lexema[i]== 0;
			if(i%4==0)
				lexema[i]=' ';
			return NUMEROS;
		}
		
		if(isalpha(c)){
			int i = 0;
			do{
			lexema[i++]=c;
			c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]== 0;
			if(i<6)
				if(lexema[0]=='0')
				 return CODIGO;
		}
		return c;
	}

}

int main(){
	if(!yyparse()) printf("cadena valida \n");
	else printf(" cadena invalida \n");
	return 0;
}
