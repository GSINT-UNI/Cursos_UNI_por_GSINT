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
	double valor; 
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

%token	ID NUM RAIZ SI SINO PARA MIENTRAS MOSTRAR ENTER COM STRING
/* variables def operacion */ TRUEASSIGN ASSIGN SUM RES MUL DIV EVAL EQ NEQ LES MOR LEQ MEQ ITERLIMIT AND OR POW SQRT /* variables def orden */ PROG VARS ELSE OTHERCASE DESDE HASTA AUMENTANDO

%%
// ESTRUCTURA DEL COMPILADOR
programa: lineas;
// ACEPTA WHILE,FOR,IFELSE,DECLARACION DE VARIABLES Y COMENTARIOS
linea: estructura 
	    | ENTER ;
lineas: linea lineas
	    | linea {$$=$1;};
	    
estructura: comentario 
	    | while
	    | for 
	    | ifelse 
	    | declaracion 
	    | print ;

declaracion: definir ';' {$$=$1;};	

asignacion : '=' ID {$$=localizaSimb(lexema, ID);}  expresion {int elements[totalFields] = {$3, $4};int i = generaCodigo(ASSIGN, elements,2); evalCodigo(i);$$=i;} ;

definir: asignacion ',' definir 
	    | asignacion ;	
	        
//DEFINO OPERACIONES BASICAS CON PRECEDENCIA
expresion: '+' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(SUM, elements,3);evalCodigo(j);$$=i;}			
	    | '-' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(RES, elements,3);evalCodigo(j);$$=i;}			 
	    | producto {$$=$1;};

producto: '*' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(MUL, elements,3);evalCodigo(j);$$=i;}			
	    | '/' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(DIV, elements,3);evalCodigo(j);$$=i;}			
	    | agrupacion {$$=$1;};
	    
//DEFINO AGRUPACIONES MEDIANTE POTENCIA Y RAIZ.
agrupacion:'^' expresion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo(POW, elements,3);evalCodigo(j);$$=i;}	
	    | RAIZ '(' expresion ')' {int i=GenVarTemp();int elements[totalFields] = {i, $3};int j=generaCodigo(SQRT, elements,2);evalCodigo(j);$$=i;}		 
	    | valor   {$$=$1;};
	    
//EL COMPILADOR ACEPTA VALORES NUMERICOS, VARIABLES, ejm : x, 5 , 3 , etc
valor: NUM {$$=localizaSimb(lexema,NUM);}
	    | ID {$$=localizaSimb(lexema,ID);} 
	    | STRING	{$$=localizaSimb(lexema,STRING);};
	    

//DEFINO IFELSE
ifelse: SI '(' lista_condicion ')' {evalFlag=evalCondition($3);} '{'
	{
		elseFlag = (evalFlag+1)%2;		
	} lineas '}' else ;
	
else: SINO { evalFlag=elseFlag; } '{' lineas '}' {evalFlag=1;} ;
    
//LISTA DE CONDICIONES
lista_condicion: operadorlogico '('lista_condicion')' '('lista_condicion ')'	{int i=GenVarTemp();int elements[totalFields] = {i, $3, $6};int j=generaCodigo($1, elements,3);evalCodigo(j);$$=i;}
	    | condicion 	{$$=$1;};

operadorlogico: '&' 	{$$=AND;}
	    | '|''|'	{$$=OR;};
	    
condicion: orden condicion expresion {int i=GenVarTemp();int elements[totalFields] = {i, $2, $3};int j=generaCodigo($1, elements,3);evalCodigo(j);$$=i;}
	    | expresion	{$$=$1;};


//OPERADORES DE ORDEN (<,>,=,!)
orden: '=''='	{$$=EQ;}
			|	'!''='	{$$=NEQ;}
			|	'<'		{$$=LES;}
			|	'>'		{$$=MOR;}
			|	'=''<'	{$$=LEQ;}
			|	'=''>'	{$$=MEQ;};
	    
//DEFINO FOR
for: PARA '(' asignacion ';'{$$=cx+1;} condicion {$$=cx;} {evalFlag=0;}';' {$$=cx;} asignacion {$$=cx;}')' {evalFlag=0;} '{' lineas {
						int A1=$5; //primer $$
						int A2=$7; //segundo $$

						int B1=$10+1; //tercer $$ + 1
						int B2=$12; // cuarto $$

						int C1=B2+1;
						int C2=cx;

						duplicate(A1, A2);
						int CX=moveToEnd(B1, B2);
						evalFlag=1;
						while(evalCondition($6)) // statement
						{
							evalLoop(A1,CX);
						}
					} '}' ;

//contador: '=' ID expresion ;

//DEFINO WHILE
while: MIENTRAS '(' {$$=cx+1;} lista_condicion {$$=cx;}{evalFlag=evalCondition($4);}')' '{' {evalFlag=0;} lineas {
						//printf("#REG%d#", $4);
						int A=$3;
						int B=$5;
						int C=cx; 
						duplicate(A, B);
						evalFlag=1;
						while(evalCondition($4))
						{
							evalLoop(A,C+B-A+1);
						}
					} '}'{evalFlag=1;} ;

//IMPRIMIR TEXTO
print: ID {$$=localizaSimb(lexema, ID);} '(' valor {evalBuffer[bufferUsed++]=$4;} ')' {int *elements = append($2, evalBuffer, bufferUsed);bufferUsed=0;int i = generaCodigo(EVAL,elements,totalFields); $$=evalCodigo(i);} ';' 	;

/*printbuffer: valor			{evalBuffer[bufferUsed++]=$1;}
	    | valor ',' printbuffer	{evalBuffer[bufferUsed++]=$1;};*/
	    
//HABILIDAD PARA AGREGAR COMENTARIO CON LA FORMA: # comentario $
comentario: '#' comen '$';

//agrego esto para que los comentarios puedan tener cualquier palabra incluso las instrucciones.
comen: comen ID | comen SI | comen SINO | comen PARA | comen MIENTRAS | comen RAIZ | comen ',' | comen ENTER | ;


%%



void yyerror(char *msg){
	printf("error: %s", msg);
}

int GenVarTemp(){
	char t[60];
	sprintf(t, "_T%d", nVarTemp++);
	return localizaSimb(t, ID);
}

int reservedWord(char lexema[]){

	/*if(strcasecmp(lexema,"cuando")==0) return IF;
	if(strcasecmp(lexema,"sino")==0) return ELSE;
	if(strcasecmp(lexema,"otroCaso")==0) return OTHERCASE;
	if(strcasecmp(lexema,"ifelse")==0) return IFELSE;
	if(strcasecmp(lexema,"while")==0) return WHILE;
	if(strcasecmp(lexema,"calcular")==0) return FOR;
	if(strcasecmp(lexema,"def")==0) return DEF;
	if(strcasecmp(lexema,"Programa")==0) return PROG;
	if(strcasecmp(lexema,"Vars")==0) return VARS;
	if(strcasecmp(lexema,"desde")==0) return DESDE;
	if(strcasecmp(lexema,"hasta")==0) return HASTA;
	if(strcasecmp(lexema,"aumentando")==0) return AUMENTANDO;
	return ID;*/
	if( strcmp( lexema, "si" ) == 0 ) return SI;
	if( strcmp( lexema, "sino" ) == 0 ) return SINO;
	if( strcmp( lexema, "para" ) == 0 ) return PARA;
	if( strcmp( lexema, "mientras" ) == 0 ) return MIENTRAS;
	if( strcmp( lexema, "raiz" ) == 0 ) return RAIZ;
	if( strcmp( lexema, "mostrar" ) == 0 ) return MOSTRAR;
	return ID;
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
		if(!strcasecmp(TablaSim[i].nombre, nom))
			return i;
	}
	strcpy(TablaSim[nSim].nombre, nom);
	TablaSim[nSim].token = tok;
	if(tok == STRING) strcpy(mensajes, nom);
	if(tok == ID) TablaSim[nSim].valor=0.0;
	if(tok == NUM) sscanf(nom, "%lf", &TablaSim[nSim].valor);
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
	if(operation==SUM){TablaSim[element1].valor = TablaSim[element2].valor + TablaSim[element3].valor;}
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
		printf("%-20s\t", tokenList[TCodigo[i].op - 269]);
		printf("fields: [");
		int j;
		for(j = 0; j < totalFields; j++){printf("%d, ", TCodigo[i].aArray[j]);}
		printf("]\n");
		//printf("%d a1=%d a2=%d a3=%d\n", TCodigo[i].op, TCodigo[i].a1, TCodigo[i].a2, TCodigo[i].a3);
	}
}

int yylex(){
	char c;
	while(1){
		c = getchar();
		if (isspace(c)) continue;
		if (c == '\t') continue;
		if (c == ',') return COM;
		if (c == '\n') return ENTER;
		

		if (isalpha(c)) {
			int i = 0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));

			ungetc(c, stdin);
			lexema[i] = 0;
			return reservedWord(lexema);
		}

		if (c == '"') {
			int i = 0;
			int closureQuote = 0;
			int closureQuoteConfirm = 0;
			do{
				if(closureQuote){closureQuoteConfirm = 1;}
				lexema[i++]=c;
				c=getchar();
				if(c == '"'){closureQuote = 1;}
			}while(!closureQuoteConfirm);

			ungetc(c, stdin);
			lexema[i] = 0;
			return STRING;
		}

		if (isdigit(c)){
			int decimalFlag = 0;
			int decimalReaded = 0;
			int i = 0;
			do{
				if (decimalFlag){decimalReaded = 1;}
				lexema[i++]=c;
				c=getchar();
				if( c == '.' || c == 'e' || c == 'E' ){decimalFlag = 1;}
			}while((isdigit(c)) || (( c == '.' || c == 'e' || c == 'E' )&&(!decimalReaded)));

			ungetc(c, stdin);
			lexema[i] = 0;
			return NUM;
		}
		return c;
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
