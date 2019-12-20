%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
char lexema[255];
void yyerror(char *);

/*VARIABLES PARA GENERACION DE TABLAS*/
typedef struct {
	char nombre[255]; 
	float valor; 
	int token;
}tipoTS;
tipoTS TablaSim[100];
int nSim=0;

#define totalFields 6
#define totalCodes 100
typedef struct{
	int op; 
	int aArray[totalFields]
}tipoCodigo;
int cx=-1;
tipoCodigo TCodigo[totalCodes];

int generaCodigo(int, int[], int);
int localizaSimb(char*, int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();


/*VARIABLES PARA GENERACION DE DE ARGUMENTOS A USAR EN EL LENGUAJE*/

int* getElements(int*, int); // Genera arreglo de componentes para ser usados como argumentos
int evalCondition(int);
int evalFlag=1;

void evalLoop(int codeA, int codeB);
void duplicate(int codeA, int codeB);
int loopFlag=0;

char tokenList[18][30];

int iterationIndexA, iterationIndexB;

int evalBuffer[totalFields];
int bufferUsed = 0;
int* append(int, int*, int);

int elseFlag = 0;
int otherCaseFlag = 0;

char mensajes[300];

%}

%union {
	float ftype;
	char *stype;
	int itype;
}

%token	ID NUM RAIZ SI SINO PARA MIENTRAS ENTER COM STRING
/* variables def operacion */ TRUEASSIGN ASSIGN SUM RES MUL DIV EVAL EQ NEQ LES MOR LEQ MEQ ITERLIMIT AND OR POW SQRT /* variables def orden */ PROG VARS ELSE OTHERCASE DESDE HASTA AUMENTANDO

%type <ftype> expresion producto agrupacion 
%type <itype> lista_condicion
%type <stype> ID STRING
%%
// ESTRUCTURA DEL COMPILADOR
programa: lineas;
// ACEPTA WHILE,FOR,IFELSE,DECLARACION DE VARIABLES Y COMENTARIOS
linea: estructura 
	    | ENTER ;
lineas: linea lineas
	    | linea ;
	    
estructura: while
	    | for 
	    | ifelse 
	    | declaracion 
	    | print ;

declaracion: definir ';' ;	

asignacion : '=' ID {$<itype>$=localizaSimb($<stype>2, ID);} expresion {int elements[totalFields] = {$<stype>3, $4}; int i = generaCodigo(ASSIGN,elements,2); evalCodigo(i);$<itype>$=i;} ;

definir: asignacion ',' definir 
	    | asignacion ;	
	        
//DEFINO OPERACIONES BASICAS CON PRECEDENCIA
expresion: '+' expresion expresion {/*printf("v1:%f,%f,v2:%f,%f",$2,TablaSim[(int)$2].valor,$3,TablaSim[(int)$3].valor);*/int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(SUM, elements,3);evalCodigo(j);$$=i;}			
	    | '-' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(RES, elements,3);evalCodigo(j);$$=i;}			 
	    | producto {$$=$1;};

producto: '*' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(MUL, elements,3);evalCodigo(j);$$=i;}			
	    | '/' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(DIV, elements,3);evalCodigo(j);$$=i;}			
	    | agrupacion {$$=$1;};
	    
//DEFINO AGRUPACIONES MEDIANTE POTENCIA Y RAIZ.
agrupacion:'^' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(POW, elements,3);evalCodigo(j);$$=i;}	
	    | RAIZ '(' expresion ')' {int i=GenVarTemp();int elements[totalFields] = {i, $3};int j=generaCodigo(SQRT, elements,2);evalCodigo(j);$$=i;}		 
	    | valor   {$$=$<ftype>1;};
	    
//EL COMPILADOR ACEPTA VALORES NUMERICOS, VARIABLES, ejm : x, 5 , 3 , etc
valor: NUM {$<ftype>$=localizaSimb($<stype>1,NUM);}
	    | ID {$<ftype>$=localizaSimb($1,ID);} 
	    | STRING	{$<stype>$=localizaSimb($1,STRING);};
	    

//DEFINO IFELSE
ifelse: SI '(' lista_condicion ')' {evalFlag=evalCondition($<itype>3);} '{'
	{
		elseFlag = (evalFlag+1)%2;		
	} lineas '}' else ;
	
else: SINO { evalFlag=elseFlag; } '{' lineas '}' {evalFlag=1;} ;
    
//LISTA DE CONDICIONES
lista_condicion: operadorlogico '('lista_condicion')' '('lista_condicion ')'	{int i=GenVarTemp();int elements[totalFields] = {i, $3, $6};int j=generaCodigo($<itype>1, elements,3);evalCodigo(j);$$=i;}
	    | condicion 	{$$=$<itype>1;};

operadorlogico: '&' 	
	    | "||"	;
	    
condicion: orden condicion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $<itype>2, $3};int j=generaCodigo($<itype>1, elements,3);evalCodigo(j);$<itype>$=i;}
	    | expresion	{$<itype>$=$1;};


//OPERADORES DE ORDEN (<,>,=,!)
orden: '=''='	{$<itype>$=EQ;}
			|	'!''='	{$<itype>$=NEQ;}
			|	'<'		{$<itype>$=LES;}
			|	'>'		{$<itype>$=MOR;}
			|	'=''<'	{$<itype>$=LEQ;}
			|	'=''>'	{$<itype>$=MEQ;};
	    
//DEFINO FOR
for: PARA '(' asignacion ';'{$<itype>$=cx+1;} condicion {$<itype>$=cx;} {evalFlag=0;}';' {$<itype>$=cx;} asignacion {$<itype>$=cx;}')' {evalFlag=0;} '{' lineas {
						int A1=$<itype>5; //primer $$
						int A2=$<itype>7; //segundo $$

						int B1=$<itype>10+1; //tercer $$ + 1
						int B2=$<itype>12; // cuarto $$

						int C1=B2+1;
						int C2=cx;

						duplicate(A1, A2);
						int CX=moveToEnd(B1, B2);
						evalFlag=1;
						while(evalCondition($<itype>6)) // statement
						{
							evalLoop(A1,CX);
						}
					} '}' ;

//contador: '=' ID expresion ;

//DEFINO WHILE
while: MIENTRAS '(' {$<itype>$=cx+1;} lista_condicion {$<itype>$=cx;}{evalFlag=evalCondition($<itype>4);}')' '{' {evalFlag=0;} lineas {
						//printf("#REG%d#", $4);
						int A=$<itype>3;
						int B=$<itype>5;
						int C=cx; 
						duplicate(A, B);
						evalFlag=1;
						while(evalCondition($<itype>4))
						{
							evalLoop(A,C+B-A+1);
						}
					} '}'{evalFlag=1;} ;

//IMPRIMIR TEXTO
print: ID {$<itype>$=localizaSimb($1, ID);} '(' valor {evalBuffer[bufferUsed++]=$<stype>4;} ')' {int *elements = append($<itype>2, evalBuffer, bufferUsed);bufferUsed=0;int i = generaCodigo(EVAL,elements,totalFields); $<itype>$=evalCodigo(i);} ';' 	;

/*printbuffer: valor			{evalBuffer[bufferUsed++]=$1;}
	    | valor ',' printbuffer	{evalBuffer[bufferUsed++]=$1;};*/
	    

%%



void yyerror(char *msg){
	printf("error: %s", msg);
}

int GenVarTemp(){
	char t[60];
	sprintf(t, "_T%d", nVarTemp++);
	return localizaSimb(t, ID);
}

int* append(int a, int* b, int nb){
	int index = 0;
	int i, j;
	int *result = (int*)malloc(sizeof(int)*totalFields);
	for(i = 0; i < totalFields; i++){result[i]=-1;}
	result[index++] = a;
	for(j = 0; (j < nb) && (index < totalFields); j++){
		result[index++] = b[j];
	}
	return result;
}

int getTrueValue(int va, int op, int vb){
	int a = TablaSim[va].valor;
	int b = TablaSim[vb].valor;
	//printf("Evaluando:%s %d %s:", TablaSim[va].nombre, op, TablaSim[vb].nombre);

	if(op==EQ){return (a == b);}
	else if(op==NEQ){return (a != b);}
	else if(op==LES){return (a < b);}
	else if(op==MOR){return (a > b);}
	else if(op==LEQ){return (a <= b);}
	else if(op==MEQ){return (a >= b);}
	else if(op==AND){return (a && b);}
	else if(op==OR){return (a || b);}
}

int* getElements(int* elements, int totalElements){
	int resultElements[totalFields];
	int i;
	for(i = 0; i < totalFields; i++){
		if(i < totalElements){
			resultElements[i] = elements[i];
		} else {
			resultElements[i] = -1;
		}
	}
	return resultElements;
}

int localizaSimb(char *nom, int tok){
	int i;
	for(i = 0; i<nSim; i++){
		if(!strcasecmp(TablaSim[i].nombre, nom)){
			/*printf("\n");*/		
			return i;			
		}
		/*printf("%s: nombre %s ",nom,TablaSim[i].nombre);*/
		
	}/*printf("\n");*/
	strcpy(TablaSim[nSim].nombre, nom);
	TablaSim[nSim].token = tok;
	if(tok == STRING) {printf("LLALLALALASDSADA");strcpy(mensajes, nom);}
	if(tok == ID) TablaSim[nSim].valor=0.0;
	if(tok == NUM) sscanf(nom, "%f", &TablaSim[nSim].valor);
	nSim++;
	return nSim-1;
}

int generaCodigo(int op, int aArray[], int usefulFields){
	cx++;
	TCodigo[cx].op=op;
	int i;
	for(i = 0; i < totalFields; i++){
		if(i < usefulFields){
			//resultElements[i] = elements[i];
			TCodigo[cx].aArray[i] = aArray[i];
			//printf("f%d %d",i,aArray[i]);////////////////FLAGGG////////////////
		} else {
			//resultElements[i] = -1;
			TCodigo[cx].aArray[i] = -1;
		}
	}
	return cx;
}

void evalCodigo(int index){
	if (!evalFlag)
		return;

	int operation = TCodigo[index].op;
	int *elementsArr = TCodigo[index].aArray;

	int element1 = elementsArr[0];
	int element2 = elementsArr[1];
	int element3 = elementsArr[2];

	if(operation==TRUEASSIGN){TablaSim[element1].valor = element2;}
	if(operation==ASSIGN){TablaSim[element1].valor = TablaSim[element2].valor;}
	if(operation==SUM){TablaSim[element1].valor = TablaSim[element2].valor + TablaSim[element3].valor;/*printf("re:%f = v1:%f + v2:%f ",TablaSim[element1].valor,TablaSim[element2].valor,TablaSim[element3].valor);*/}
	if(operation==RES){TablaSim[element1].valor = TablaSim[element2].valor - TablaSim[element3].valor;}
	if(operation==MUL){TablaSim[element1].valor = TablaSim[element2].valor * TablaSim[element3].valor;}
	if(operation==DIV){TablaSim[element1].valor = TablaSim[element2].valor / TablaSim[element3].valor;}
	if(operation==POW){TablaSim[element1].valor = pow(TablaSim[element2].valor , TablaSim[element3].valor);}
	if(operation==SQRT){TablaSim[element1].valor = sqrt(TablaSim[element2].valor );}

	if(operation==EQ){TablaSim[element1].valor = TablaSim[element2].valor == TablaSim[element3].valor;}
	if(operation==NEQ){TablaSim[element1].valor = TablaSim[element2].valor != TablaSim[element3].valor;}
	if(operation==LES){TablaSim[element1].valor = TablaSim[element2].valor < TablaSim[element3].valor;}
	if(operation==MOR){TablaSim[element1].valor = TablaSim[element2].valor > TablaSim[element3].valor;}
	if(operation==LEQ){TablaSim[element1].valor = TablaSim[element2].valor <= TablaSim[element3].valor;}
	if(operation==MEQ){TablaSim[element1].valor = TablaSim[element2].valor >= TablaSim[element3].valor;}
	if(operation==AND){TablaSim[element1].valor = TablaSim[element2].valor && TablaSim[element3].valor;}
	if(operation==OR){TablaSim[element1].valor = TablaSim[element2].valor || TablaSim[element3].valor;}
	
	if(operation==EVAL){evalFunction(elementsArr);}
	
}

void duplicate(int codeA, int codeB){
	for(int i = codeA; i <= codeB; i++){
		int op = TCodigo[i].op;
		int* aArray = TCodigo[i].aArray;
		int usefulFields = 0;
		while(TCodigo[i].aArray[usefulFields] != -1){usefulFields++;}

		generaCodigo(op, aArray, usefulFields);
	}
}

void moveToEnd(int codeA, int codeB){
	int numCodes = codeB - codeA + 1;
	duplicate(codeA, codeB);
	int i;
	for(i = codeB+1; i <= cx; i++){
		TCodigo[i-numCodes] = TCodigo[i];
	}
	cx = cx - numCodes;
	return(cx);
}

void evalLoop(int codeA, int codeB){
	int j;
	//printf("[%d->%d]", codeA, codeB);
	for(j = codeA; j <= codeB; j++){
		evalCodigo(j);
	}
}

int evalCondition(int index){
	if(TablaSim[index].valor){
		return 1;
	} else {
		return 0;
	}
}

int evalFunction(int* fields){
	char* funName = TablaSim[fields[0]].nombre;	
			
	if(strcasecmp(funName, "nImprimir")==0){
		for(int i = 1; i < totalFields; i++){
			if((fields[i] < nSim)&&(fields[i] != -1)){
				printf("%lf ", TablaSim[fields[i]].valor);
			}
		}
		printf("\n");
	} else if(strcasecmp(funName, "sImprimir")==0){
		printf("%s", mensajes);	
	} else if(strcasecmp(funName, "sqrt")==0){
		double result = sqrt(TablaSim[fields[1]].valor);
		
		char milexema[50];
		snprintf(milexema, 50, "%lf", result);
		
		int indice_valor = localizaSimb(milexema, NUM);
		int indice_contenedor = GenVarTemp();
		int elements[totalFields] = {indice_contenedor, indice_valor};
		int j=generaCodigo(ASSIGN, elements,2);
		evalCodigo(j);
		return indice_contenedor;
	}
	return -1;
}

void imprimeTablaSim(){
	int i;
	for(i = 0; i < nSim; i++){
		printf("%d nombre=%-10s\ttok=%d | valor=%lf\n", i, TablaSim[i].nombre, TablaSim[i].token, TablaSim[i].valor);
	}
}

void imprimeTablaCod(){
	int i;
	for(i = 0; i <= cx; i++){
		printf("%d:", i);
		printf("%-20s\t", tokenList[TCodigo[i].op - 268]);
		printf("fields: [");
		int j;
		for(j = 0; j < totalFields; j++){printf("%d, ", TCodigo[i].aArray[j]);}
		printf("]\n");
		//printf("%d a1=%d a2=%d a3=%d\n", TCodigo[i].op, TCodigo[i].a1, TCodigo[i].a2, TCodigo[i].a3);
	}
}

void initTokenStrings(){
	strcpy(tokenList[0], "TRUEASSIGN");
	strcpy(tokenList[1], "ASSIGN");
	strcpy(tokenList[2], "SUM");
	strcpy(tokenList[3], "RES");
	strcpy(tokenList[4], "MUL");
	strcpy(tokenList[5], "DIV");
	strcpy(tokenList[6], "EVAL");
	strcpy(tokenList[7], "EQ");
	strcpy(tokenList[8], "NEQ");
	strcpy(tokenList[9], "LES");
	strcpy(tokenList[10], "MOR");
	strcpy(tokenList[11], "LEQ");
	strcpy(tokenList[12], "MEQ");
	strcpy(tokenList[13], "ITERLIMIT");
	strcpy(tokenList[14], "AND");
	strcpy(tokenList[15], "OR");
	strcpy(tokenList[16], "POW");
	strcpy(tokenList[17], "SQRT");
}

int main(){
	initTokenStrings();
	int exe = yyparse(); // Ejecucion del compilador
	printf("\n==============================\n"); // Linea divisora de outputs
	if (!exe) printf("cadena valida \n");
	else printf(" cadena invalida");

	printf("Tabla de simbolos\n");
	imprimeTablaSim();
	printf("\nTabla de codigos\n");
	imprimeTablaCod();

	return 0;
}
