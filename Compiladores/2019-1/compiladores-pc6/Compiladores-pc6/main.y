%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char lexema[60];
void yyerror(char *msg);

//tabla de simbolos
typedef struct{
  char nombre [60];
  double valor ;
  int token;
}tipoTS;


tipoTS TablaSim[100];
int nSim=0;

//tabla de codigo
typedef struct{
  int op;
  int a1;
  int a2;
  int a3;
}tipocodigo;

int cx=-1;
tipocodigo TCodigo[100];
void generarCodigo(int , int ,int , int);
int localizaSimb(char *,int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();
int generar=1;

%}


%token MAYOR MENOR ESIGUAL MAYOR_IGUAL MENOR_IGUAL
%token AND OR Q

%token MAS MENOS POR ENTRE POWER
%token SUMAE RESTAE MASMAS MENOSMENOS MASIGUAL MENOSIGUAL

%token DOUBLE_DOTS SEMICOLON COMA
%token EQUAL IGUAL

%token CORCHS_INIT CORCHS_FIN
%token PARENTS_INIT PARENTS_FIN
%token KEYS_INIT KEYS_FIN

%token NUMBER TEXT

%token QUOTES SEMIQUOTES

%token CONST LET
%token NUMBER_TYPE STRING_TYPE VOID_TYPE BOOL_TYPE
%token OF CONTINUE BREAK NEW

%token STATIC

%token PUBLIC PRIVATE

%token IF ELSE DO WHILE
%token FOR SWITCH CASE DEFAULT

%token FUNCTION CLASS
%token RETURN
%token CLASS_TYPE FUNCTION_TYPE
%%
main_line : main_line main_line_type 
					| ;
main_line_type : asign_all 
               | ifelse 
               ;

asign_all : asign 
					| asignSuma_algo 
					| asignResta_algo ;

asign: TEXT {printf("lexema:%c\n",yychar);$$=localizaSimb(lexema,TEXT);} asign_end {printf("lexema:%s\n",lexema);generarCodigo(EQUAL,$2,$3,'-');};
asignSuma_algo: TEXT {$$=localizaSimb(lexema,TEXT);} '+' sumaE {generarCodigo(SUMAE,$2,$4,'=');}; 
asignResta_algo: TEXT {$$=localizaSimb(lexema,TEXT);} '-' restaE {generarCodigo(RESTAE,$2,$4,'=');};

asign_end:'=' valor_asignable ';'{$$=$2;};
sumaE: '=' E ';'{$$=$2;} //+=
			| '+' ';'{$$=-1;}; //++
restaE: '=' E ';'{$$=$2;} //-=
			| '-' ';'{$$=-1;}; //--
E: E '+' T { int i=GenVarTemp();generarCodigo(MAS,i,$1,$3);$$=i;};
E: E '-' T { int i=GenVarTemp();generarCodigo(MENOS,i,$1,$3);$$=i;};

E:T;

T: T '*' F { int i=GenVarTemp();generarCodigo(POR,i,$1,$3);$$=i;};
T: T '/' F { int i=GenVarTemp();generarCodigo(ENTRE,i,$1,$3);$$=i;};
T: F;

F:      P
    |   F '^' P { int i=GenVarTemp();generarCodigo(POWER,i,$1,$3);$$=i;};
P:  valor_operable
    | '(' E ')' { $$=$2;}
;

valor_operable: NUMBER {$$=localizaSimb(lexema,NUMBER);}
		|TEXT  {$$=localizaSimb(lexema,TEXT);};
valor_asignable: E ;

ifelse: if {generar=(generar+1)%2;} else ;

if: if_header {if(TablaSim[$1].valor==0) generar=0;} if_body;
if_header: IF '(' condition ')'{$$=$3;};
if_body : '{' main_line '}' 
				| main_line_type;

condition : condition AND comparision { int i=GenVarTemp();generarCodigo(AND,i,$1,$3);$$=i;}
					| condition OR comparision { int i=GenVarTemp();generarCodigo(OR,i,$1,$3);$$=i;}
					| comparision
					| ;
comparision :   E '>' E { int i=GenVarTemp();generarCodigo(MAYOR,i,$1,$3);$$=i;}
            |   E '<' E { int i=GenVarTemp();generarCodigo(MENOR,i,$1,$3);$$=i;}
            |   E '=''=' E { int i=GenVarTemp();generarCodigo(ESIGUAL,i,$1,$4);$$=i;}
            |   E '>' '=' E { int i=GenVarTemp();generarCodigo(MAYOR_IGUAL,i,$1,$4);$$=i;}
            |   E '<' '=' E { int i=GenVarTemp();generarCodigo(MENOR_IGUAL,i,$1,$4);$$=i;}
            |   E ;

else: ELSE if_body {generar=1;};
%%

int GenVarTemp(){
	if(generar==0) return;
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,TEXT);
}

void generarCodigo(int op, int a1,int a2, int a3){
	if(generar==0) return;
	imprimeTablaSim();

	if(op == EQUAL) TablaSim[a1].valor = TablaSim[a2].valor;

	if(op == MAS)	TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
	if(op == MENOS)	TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;

	if(op == POR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
	if(op == ENTRE) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
	if(op == POWER) TablaSim[a1].valor = pow(TablaSim[a2].valor, TablaSim[a3].valor);

	if(op == SUMAE){
		if(a2 < 0 ) { op=MASMAS; TablaSim[a1].valor++;}
		else {op == MASIGUAL; TablaSim[a1].valor+=TablaSim[a2].valor;}
	}
	if(op == RESTAE){
		if(a2 < 0 ) { op=MENOSMENOS; TablaSim[a1].valor--;}
		else {op == MENOSIGUAL; TablaSim[a1].valor-=TablaSim[a2].valor;}
	}

	if(op == MAYOR){ 
		if(TablaSim[a2].valor > TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MENOR) { 
		if(TablaSim[a2].valor < TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == ESIGUAL) {
		if(TablaSim[a2].valor == TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MAYOR_IGUAL) {
		if(TablaSim[a2].valor >= TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == MENOR_IGUAL) {
		if(TablaSim[a2].valor >= TablaSim[a3].valor) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}

	if(op == AND){
		if(TablaSim[a2].valor*TablaSim[a3].valor == 1) TablaSim[a1].valor = 1;
		else TablaSim[a1].valor = 0;}
	if(op == OR)
		if(TablaSim[a2].valor+TablaSim[a3].valor == 0) TablaSim[a1].valor = 0;
		else TablaSim[a1].valor = 1;

  cx++;
  TCodigo[cx].op=op;
  TCodigo[cx].a1=a1;
  TCodigo[cx].a2=a2;
  TCodigo[cx].a3=a3;

	imprimeTablaCod();
	imprimeTablaSim();
	printf("fin %d \n",op);
}

int localizaSimb(char *nom,int tok){
	if(generar==0) return;
  int i;
  for (i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token=tok;
  if (tok==TEXT) TablaSim[nSim].valor=0.0;
  if (tok==NUMBER) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim-1;
}

void imprimeTablaSim(){
	printf("tabla de simbolos----------------\n");
  int i;
  for ( i=0;i<nSim;i++){
    printf("%d nombre=%s tok=%d valor=%lf\n", i , TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
	printf("tabla de codigos------------------\n");
  int i;
  for ( i=0;i<=cx;i++){
    printf("%d a1=%d a2=%d a3=%d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void yyerror(char *msg){
  printf("ERROR:%s \n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera may y minusc
  //strcasecmp ignora may de min
	if(strcmp(lexema, "If") == 0) return IF;
	if(strcmp(lexema, "Else") == 0) return ELSE;

	if(strcmp(lexema, "and") == 0) return AND;
  if(strcmp(lexema, "or") == 0) return OR;
	
	if(strcmp(lexema, "continue") == 0) return CONTINUE;
  if(strcmp(lexema, "break") == 0) return BREAK;
  if(strcmp(lexema, "Number") == 0) return NUMBER_TYPE;
	//printf("retlexb:%s\n	",lexema);
  return TEXT;
}


int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		if(c=='\t') continue;
		
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalpha(c));
			ungetc(c, stdin);
			lexema[i]=0;
			
			return EsPalabraReservada(lexema);
		}
		if(isdigit(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c));
			ungetc(c, stdin);
			lexema[i]=0;
			return NUMBER;
		}
		return c;
	}
}


int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
//	printf("tabla de simbolos\n");
	imprimeTablaSim();
//	printf("tabla de codigos\n");
	imprimeTablaCod();
	
	return 0;
}





