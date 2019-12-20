%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char lexema[60];
void yyerror(char *msg);
typedef struct{
   char nombre[60];
   double valor;
   int token;
}tipoTS;
tipoTS TablaSim[100];
int nSim = 0;
typedef struct{
   int op;
   int a1;
   int a2;
   int a3;
}tipoCodigo;
int cx = -1;
tipoCodigo TCodigo[100];
void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp = 0;
int GenVarTemp();
void InterpretaCodigo();
int linea = 0;
%}

%token ID ALGORITMO INICIO FIN INICIOALGORITMO FINALGORITMO NUM VARIABLE
%token ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR PARENTESIS
%token SI SINO ENTONCES SALTARF1 SALTARF2
%token MAYOR MENOR IGUAL MAYOR_IGUAL MENOR_IGUAL

%%

inst: ALGORITMO ID INICIOALGORITMO listaInstruccion FINALGORITMO '.';
bloque: INICIO listaInstruccion FIN | instruccion bloque;
listaInstruccion: instruccion listaInstruccion | ;
instruccion: ID {$$=localizaSimb(lexema,ID);} '=' level1{generaCodigo(ASIGNAR,$2,$4,'-');} terminal;
terminal: ','|';'|;
instruccion: SI cond {generaCodigo(SALTARF1,$2,'?','-');$$=cx;} ENTONCES bloque {generaCodigo(SALTARF2,'?','-','-');$$=cx;}{TCodigo[$3].a2=cx+1;} otro {TCodigo[$6].a1=cx+1;};
otro: SINO bloque |  ;

cond: level1 '>' level1{int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
cond: level1 '<' level1{int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
cond: level1 '=''=' level1{int i = GenVarTemp(); generaCodigo(IGUAL,i,$1,$4); $$=i;};
cond: level1 '<''>' level1;
cond: level1 '>''=' level1{int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
cond: level1 '<''=' level1{int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};

level1: level1 '+' level2{int i = GenVarTemp(); generaCodigo(SUMAR,i,$1,$3); $$=i;};
level1: level1 '-' level2{int i = GenVarTemp(); generaCodigo(RESTAR,i,$1,$3); $$=i;};
level1: level2;

level2: level2 '*' level3{int i = GenVarTemp(); generaCodigo(MULTIPLICAR,i,$1,$3); $$=i;};
level2: level2 '/' level3{int i = GenVarTemp(); generaCodigo(DIVIDIR,i,$1,$3); $$=i;};
level2: level3;

level3: '(' level1 ')'{int i = GenVarTemp(); generaCodigo(PARENTESIS,i,$2,'-'); $$=i;};
level3: level4;

level4: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);};

%%
void InterpretaCodigo(){
  int i,a1,a2,a3,op;
  for(i=0; i<=cx; i++){
    op = TCodigo[i].op;
    a1 = TCodigo[i].a1;
    a2 = TCodigo[i].a2;
    a3 = TCodigo[i].a3;

    if(op==MAYOR){
         if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MENOR){
         if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MAYOR_IGUAL){
         if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==MENOR_IGUAL){
         if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==IGUAL){
         if(TablaSim[a2].valor==TablaSim[a3].valor)TablaSim[a1].valor=1;
         else
            TablaSim[a1].valor=0;
    }
    if(op==SUMAR) TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
    if(op==RESTAR) TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
    if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
    if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
    if(op==SALTARF1){
          printf("Holi, a2 = %d \n",a2);
         if(TablaSim[a1].valor==0) i=a2-1;
    }
    if(op==SALTARF2) i=a1-1;
    if(op==ASIGNAR) TablaSim[a1].valor = TablaSim[a2].valor;
  }
}

int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,ID);
}

void generaCodigo(int op, int a1, int a2, int a3){
  cx++;
  TCodigo[cx].op = op;
  TCodigo[cx].a1 = a1;
  TCodigo[cx].a2 = a2;
  TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok){
  int i;
  for(i=0; i<nSim; i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token = tok;
  if(tok==ID) TablaSim[nSim].valor = 0.0;
  if(tok==NUM) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim - 1;
}

void imprimeTablaSim(){
  int i;
  for(i=0; i<nSim; i++){
    printf("%d\tnombre = %s\ttok = %d\tvalor = %lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for(i=0; i<=cx; i++){
    printf("%d\ta1 = %d\ta2 = %d\ta3 = %d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void yyerror(char *msg){
  printf("ERROR: %s\n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcasecmp(lexema,"Algoritmo")==0) return ALGORITMO;
  if(strcasecmp(lexema,"inicioAlgoritmo")==0) return INICIOALGORITMO;
  if(strcasecmp(lexema,"finAlgoritmo")==0) return FINALGORITMO;
  if(strcasecmp(lexema,"inicio")==0) return INICIO;
  if(strcasecmp(lexema,"fin")==0) return FIN;
  if(strcasecmp(lexema,"var")==0) return VARIABLE;
  if(strcasecmp(lexema,"si")==0) return SI;
  if(strcasecmp(lexema,"sino")==0) return SINO;
  if(strcasecmp(lexema,"entonces")==0) return ENTONCES;
  return ID;
}

int yylex(){
  char c; int i;
  while(1){
    c = getchar();
    if(c==' ') continue;
    if(c=='\t') continue;
    if(c=='\n') {
      continue;
    }
    if(isdigit(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isdigit(c));
      ungetc(c,stdin);
      lexema[i] = '\0';
      return NUM;
    }
    if(isalpha(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isalnum(c));
      ungetc(c,stdin);
      lexema[i] = '\0';
      return EsPalabraReservada(lexema);
    }
    return c;
  }
}

int main(){
  if(!yyparse()) printf("La cadena es VALIDA\n");
  else printf("La cadena es INVALIDA\n");
  printf("Tabla de Simbolos:\n"); imprimeTablaSim();
  printf("Tabla de Codigos\n"); imprimeTablaCod();
  InterpretaCodigo();
  printf("Nueva tabla: despues de interpretar\n");
  imprimeTablaSim();
}

