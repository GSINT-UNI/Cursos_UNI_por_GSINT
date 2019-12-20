%{
#include <stdio.h>
#include <string.h>
char lexema[300];
void yyerror(char *);
%}

%token DEC NUM E

%%
instruccion: DEC E NUM;
%%

void yyerror(char *mgs){
	printf("error: %s",mgs);
}

int e=0, pos=1; //e=0 antes de la E, e=1 despues de la E 
				//pos=1:positivo, pos=0:negativo
int yylex(){
	char c;
	while(1)
	{
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(c=='E') {
			e=1; return E;
		}
		if(isdigit(c) || c=='-')
		{
			int i=0, d=0; // d=0: numero, d=1: decimal
			do{
				if(pos==0){
					do{
						lexema[i++]=c;
						c=getchar();
					}while(isdigit(c));
					ungetc(c,stdin);
					lexema[i]==0;
					return NUM;
				}

				else{
					if(c=='0' && i==0){
						lexema[i++]=c;
						c=getchar();
						if(c==' ' || c=='\n') return NUM;
						else return c;
					}

					if((c>'0' && c<='9') && i==0){
						lexema[i++]=c;
						c=getchar();
					}
					else if( i==1 )
					{
						if( c=='.' ) d=1;
						lexema[i++]=c;
						c=getchar();
						if(!isdigit(c)) return c;
					}
					else if((c>='0' && c<='9') && i>1){
						lexema[i++]=c;
						c=getchar();
					}
					else if(c=='-' && i==0){
						pos=0;
						lexema[i++]=c;
						c=getchar();
					}
					else return c;
				}

			}while(isdigit(c) || c=='.' || c=='-');
			ungetc(c,stdin);
			lexema[i]==0;
			if(d==1 || (d==0&&i==1&&e==0)) return DEC;
			else return NUM;
		}
		return c;
	}
}

int main(){
	if(!yyparse()) 
		printf("cadena valida\n");
	else 
		printf("cadena invalida\n");
	return 0;
}


