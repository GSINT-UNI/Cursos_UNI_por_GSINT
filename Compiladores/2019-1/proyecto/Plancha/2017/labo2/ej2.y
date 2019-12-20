%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID NUM 
%%
instruccion: instruccion  NUM ;
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

		if(isdigit(c)){
			if(c!='0'){
				int i = 0;
				do{
					lexema[i++]=c;
					if(c<'8'){
						c=getchar();
					}
					else{
						c='a';
					}
				}while(isdigit(c));
				ungetc(c,stdin);
				lexema[i]== 0;
				return NUM;
			}
		}	
		return c;
	}

}

int main(){
	if(!yyparse()) 
		printf("cadena valida \n");
	else 
		printf(" cadena invalida \n");
	return 0;
}


