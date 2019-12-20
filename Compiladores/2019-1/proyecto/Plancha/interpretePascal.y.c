%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	char lexema[60];
	void yyerror(char* msg);
	typedef	struct{ char nombre[60]; double valor; int token;}tipoTS;
	tipoTS TablaSim[100];
	int nSim=0;
	typedef struct{int op;int a1;int a2;int a3;}tipoCodigo;
	int cx=-1;
	tipoCodigo Tcodigo[100];
	void generaCodigo(int , int , int , int);
	int localizaSimb (char*, int);
	void imprimieTablaSim();
	int nVarTemp=0;
	GenVarTemp();
%}










%%
int GenVarTemp(){
	char t[60];
	sprintf(t,"_T%d",nVarTemp++);
	return localizaSimb(t,ID)
}
void generaCodigo(int op, int a1, int a2, int a3){
	cx++;
	Tcodigo[cx].op = op;
	Tcodigo[cx].op = a1;
	Tcodigo[cx].op = a2;
	Tcodigo[cx].op = a3;
}
int localizaSimb(char *nom, int tok){
	int i;
	for (i=0;i<nSim;i++){
		if(!strcasecmp(TablaSim[i].nombre,nom))
			return i;
	}
	strcpy(TablaSim[nSim].nombre,nom);
	TablaSim[nSim].token=tok;
	if(tok==ID) TablaSim[nSim].valor=0.0;
	if(tok==NUM) sscanf(nom, "%lf", &TablaSim[nSim].valor);
	nSim++;
	return nSim-1;
}
void imprimieTablaSim(){
	int i;
	for (i=0;i<n;i++){
		printf("%d nombre=%s tok=%d valor=%lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
	}
}
void imprimieTablaCod(){
	int i;
	for (i=0;i<=cx;i++){
		printf ("%d a1=%d a2%d a3=%d\n",Tcodigo[i].op,Tcodigo[i].a1,Tcodigo[i].a2,Tcodigo[i].a3);
	}
}







int EsPalabraReservada(char lexema[]){
	//strcmp considera may y minusc
	//strcasecmp ignora may y min
	if(strcasecmp(lexema,"Program")==0) return PROGRAMA;
	if(strcasecmp(lexema,"Begin")==0) return INICIO;
	if(strcasecmp(lexema,"End")==0) return FIN;
	return ID;
}


int yylex(){
	char c; int i;
	while(1){
		c=getchar();
		if(c==' ') continue;
		if(c=='\t') continue;
		if(c=='\n') continue;
		if(isdigit(c)){
			i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c,stdin);
			lexema[i]='\0';
			//lexema[i]=0;
			return NUM;
		}
		if(isalpha(c)){
			i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while (isalnum(c));
			ungetc(c,stdin);
			lexema[i]='\0';
			//lexema[i]=0;
			return EsPalabraReservada(lexema);
		}
		return c;
	}
}

int main(){
	if(!yyparse())printf("la cadena es valida\n" );
	else
		printf("La cadena es invalida\n");
		printf("tabla de simbolos\n");
		imprimieTablaSim();
		printf("tabla de codigos\n");
		imprimieTablaCod();
}