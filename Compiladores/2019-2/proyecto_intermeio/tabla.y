%{
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

using namespace std;

char lexema[60];
int yylex();
void yyerror(char *msg);
void actualiza();

int bucle_activado[100];
int bucleF=0;
int while_activado[100];
int whileI = 0;
map<int, int> whileMap;

int VERBOSE = 0;
int VERBOSE_ACTUALIZA = 0;

typedef struct{
  char nombre [60];
  double valor ;
  int token;
}tipoTS;

tipoTS TablaSim[100];
int nSim=0;

typedef struct{
	string nombre;
	int inicio;
	int fin;
}tipoFunc;

tipoFunc TablaFunc[100];
int nFunc=0;
map<int, int> funciones_pos;   // NO LLEGO A USAR ESTO
map<string, vector<int>> funciones_posiciones;   // NOMBRE DE LA FUNCION, DONDE EMPIEZA, DONDE ACABAM A DONDE REGRESA
map<int, string> llamada_info;
string tmp_name;
string tmp_call_name;
string current_function;

string tmp_func_arg;
map<string,vector<int>> funcion_argumentos;

int nmbr=0;


int retornoFunc = 0 ;


typedef struct{
  int op;
  int a1;
  int a2;
  int a3;
}tipocodigo;

int posicion_while[100];
int posicion_while_I = 0;
int posicion_for = 0;
int cotaI = 0;
int cota_inferior[100];
int cota_superior[100];

map<int, int> cotas;

int cx=-1;
tipocodigo TCodigo[100];
void generarCodigo(int , int ,int , int);
int localizaSimb(char *,int);
void imprimeTablaSim();
void imprimeTablaCod();
int nVarTemp=0;
int GenVarTemp();

void asignar_cotas(int x,int d){
	cota_inferior[cotaI] = (int)TablaSim[x].valor;
	cota_superior[cotaI] = (int)TablaSim[d].valor;
}

%}

%union {
	float ftype;
	char *stype;
	int itype;
}

%token PROGRAMA PROG_INICIO PROG_FIN      				
%token DESDE FIN_DESDE HASTA HACER  BUCLE BUCLE_1 BUCLE_2 SALTARF3   	
%token MIENTRAS FIN_MIENTRAS SALTARF4 SALTARF5 WHILE
%token SI FIN_SI SINO SALTARF1 SALTARF2										
%token SUMAR RESTAR MULTIPLICAR DIVIDIR MODULO PARENTESIS RAIZ POT		
%token MAYOR MENOR IGUAL MAYOR_IGUAL MENOR_IGUAL    		
%token IMPRIMIR ASIGNAR DEF CALL POSFUNCION SALIRFUNCION LLAMADAFUNC
%token NUM ID

%type <ftype> expresion producto agrupacion
%type <itype> condicion
%type <stype> ID

%%



s : PROGRAMA ':'  PROG_INICIO listaInstr PROG_FIN '.' ;

listaInstr: asignacion listaInstr 
		| bloque_if listaInstr
		| bucle_for listaInstr 
		| bucle_while listaInstr 
		| imprimir listaInstr
		| defFunc listaInstr
		| callFunc listaInstr
		| ;

defFunc: DEF ID {
					tmp_name = $<stype>2;
					generarCodigo(POSFUNCION,cx+1,'-','-');
							$<itype>$=cx;
						}'(' args ')' 
							
						 '{' listaInstr '}' {
						generarCodigo(SALIRFUNCION,cx+1,'-','-');
						TCodigo[$<itype>3].a2=cx;
						funciones_posiciones.insert({tmp_name,{TCodigo[$<itype>3].a1,TCodigo[$<itype>3].a2,0}});
							
														$<itype>$ = cx;
	
						if(VERBOSE) printf("SALIRFUNCION saliendo ... \n");$<itype>$ = cx;
						} ;

callFunc: CALL ID {tmp_call_name=$<stype>2;} '(' args ')' ';' {llamada_info.insert({cx+1,tmp_call_name});
			generarCodigo(LLAMADAFUNC,'-','-','-');};

args: args ',' ID {$<itype>$=localizaSimb($<stype>3,ID);}
| ID {$<itype>$=localizaSimb($<stype>1,NUM);} 
| args ',' NUM { $<itype>$=localizaSimb($<stype>3,NUM); } 
| NUM { $<itype>$=localizaSimb($<stype>1,NUM); } 
|;

asignacion: ID 
					{$<ftype>$ = localizaSimb($<stype>1,ID); } 
			'=' expresion 
					{ 
					  if(VERBOSE){ printf("generando en asignacion...\n");
					  printf("$2 es %f y $4 es %f \n");
					  //printf("TCodigo[%d].valor es %f \n",$2,TCodigo[$2].a1);

					}
					  generarCodigo(ASIGNAR,$<ftype>2,$4,'-');
					}
			';';


bucle_for: DESDE valor HASTA valor HACER 
						{ bucleF=100; } 
						{ 
							generarCodigo(SALTARF3,$<ftype>2,$<ftype>4,'-');
							posicion_for=cx; 
							$<itype>$ = cx; 
						} 
		  ':' listaInstr FIN_DESDE
		  				{ 
							generarCodigo(BUCLE,'?','-','-'); 
							$<itype>$ = cx;
						} 
						{ TCodigo[$<itype>7].a3=cx; }
						{ 
							//if(VERBOSE) printf("$11 es %d \n",$11);
							TCodigo[$<itype>11].a1=cx+1 ;
							TCodigo[$<itype>11].a2=posicion_for ;
						};

bucle_while: MIENTRAS '(' condicion ')'  
						{
							generarCodigo(SALTARF4,$3,'-','-');
							posicion_while[posicion_while_I++]=cx;
							$<itype>$=cx;
						}
			':' listaInstr FIN_MIENTRAS
						{generarCodigo(WHILE,'?','-','-');$<itype>$=cx;}
						{
							if(VERBOSE) printf("$5 es %d TCodigo[$5].a2 sera %d\n",$<itype>5,cx);
							TCodigo[$<itype>5].a2=cx;}
						{
							if(VERBOSE) printf("$9 es %d , TCodigo[$9].a1 sera %d \n",$<itype>9,cx+1);
							TCodigo[$<itype>9].a1=cx+1;
							TCodigo[$<itype>9].a2=posicion_while[--posicion_while_I];
						}
			;




bloque_if: SI '('condicion')' 
					{
						if(VERBOSE) printf("generando En el bloque_if...\n");
						generarCodigo(SALTARF1,$3,'-','-');
						if(VERBOSE) printf("$3 es %d\n",$<itype>3);$<itype>$ = cx;
					} 
		':'  listaInstr FIN_SI
					{ 
						generarCodigo(SALTARF2,'?','-','-');
						if(VERBOSE) printf("Saltarf2 generando en bloque_if, ? es %d\n",'?');$<itype>$ = cx;
					}
					{
						TCodigo[$<itype>5].a2=cx+1;
						if(VERBOSE) printf("Valor de $5: %d Valor de cx: %d TCodigo[$5].a2 es %f \n",$<itype>5,cx,(double)cx+1);
					} 
		otro 
					{ if(VERBOSE) printf("$9 es %d, TCodigo[$9].a1 sera %d\n",$<itype>9,cx+1);TCodigo[$<itype>9].a1=cx+1; }
		;

otro: SINO '{' listaInstr '}'|  ;


condicion: expresion '>' expresion
				{ int i = GenVarTemp(); generarCodigo(MAYOR,i,$1,$3); $$ = i; };
condicion: expresion '<' expresion
				{ int i = GenVarTemp(); generarCodigo(MENOR,i,$1,$3); $$ = i; };
condicion: expresion '=''=' expresion
				{ int i = GenVarTemp(); generarCodigo(IGUAL,i,$1,$4); $$ = i; };
condicion: expresion '>''=' expresion
					{ 
						int i = GenVarTemp(); 
						generarCodigo(MAYOR_IGUAL,i,$1,$4); 
						$$=i;
					};
condicion: expresion '<''=' expresion
					{ 
						if(VERBOSE) printf("genero codigo En la condicion...\n");
						int i = GenVarTemp(); 
						generarCodigo(MENOR_IGUAL,i,$1,$4); $$=i;
					};

imprimir: IMPRIMIR expresion 
					{ generarCodigo(IMPRIMIR,$2,'-','-'); }
					{ if(VERBOSE) printf("Visualizando:=%d\n",$2); }
			';';



expresion: expresion '+' producto 
			{ int i = GenVarTemp(); generarCodigo(SUMAR,i,$1,$3); $$ = i;};
expresion: expresion '-' producto 
			{ int i = GenVarTemp(); generarCodigo(RESTAR,i,$1,$3); $$ = i;};
expresion: expresion '#' producto 
			{ int i = GenVarTemp(); generarCodigo(MODULO,i,$1,$3); $$ = i;};
expresion:producto;
producto: producto '*' agrupacion 
			{ int i = GenVarTemp(); generarCodigo(MULTIPLICAR,i,$1,$3); $$=i;};
producto: producto '/' agrupacion 
			{ int i = GenVarTemp(); generarCodigo(DIVIDIR,i,$1,$3); $$=i;};
producto: agrupacion;
agrupacion: RAIZ '[' expresion ']'             { int i = GenVarTemp(); generarCodigo(RAIZ,i,$3,'-'); $$ = i; } 
       | POT '[' expresion ',' expresion ']'   { int i = GenVarTemp(); generarCodigo(POT,i,$3,$5); $$ = i; } ;

agrupacion: '(' expresion ')' 
				{
					if(VERBOSE) printf("Generando en parentesis...\n");
					int i = GenVarTemp(); 
					generarCodigo(PARENTESIS,i,$2,'-'); 
					$$=i;
				}
	  		| valor {$$=$<ftype>1;};

valor: NUM 	{ $<ftype>$=localizaSimb($<stype>1,NUM);}
	  | ID 	{ $<ftype>$=localizaSimb($<stype>1,ID);};


%%

map<int, string> operaName = {{MAYOR, "mayor"}, {MENOR, "menor"}, {MAYOR_IGUAL, "mayor igual"}, 
    {MENOR_IGUAL, "menor igual"}, {IGUAL, "igual"}, {SUMAR, "sumar"}, {RESTAR, "restar"}, {MODULO, "modulo"},
    {MULTIPLICAR, "multiplicar"}, {DIVIDIR, "dividir"}, {PARENTESIS, "parentesis"}, 
	{RAIZ, "raiz"}, {POT, "pot"},
    {SALTARF1, "saltar f1"}, {SALTARF2, "saltar f2"}, {SALTARF3, "saltar f3"},
    {SALTARF4, "saltar f4"}, {SALTARF5, "saltar f5"},
    {BUCLE, "bucle"}, {WHILE, "while"}, {ASIGNAR, "asignar"}, {IMPRIMIR, "imprimir"} ,{POSFUNCION,"definir"} , {SALIRFUNCION,"salirFuncion"}, {LLAMADAFUNC,"llamandoFuncion"}};

int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,ID);
}

void imprimeTablaSim(){
  int i;
  for ( i=0;i<nSim;i++){
    printf("%d nombre=%s tok=%d valor=%lf\n", i , TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for ( i=0;i<=cx;i++){
    printf("%03d %s a1=%d a2=%d a3=%d\n", i, operaName[TCodigo[i].op].c_str(),TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);

  }
}

void generarCodigo(int op, int a1,int a2, int a3){
  cx++;
  //printf("XD %d\n",cx);
  //printf("Poniendo en la tabla de codigo:\n");
  //printf("op=%d a1=%d a2=%d a3=%d \n",op,a1,a2,a3);
  TCodigo[cx].op=op;
  TCodigo[cx].a1=a1;
  TCodigo[cx].a2=a2;
  TCodigo[cx].a3=a3;
  //printf("Despues de modificar la tabla de codigo...\n");
  //imprimeTablaCod();
}

int localizaSimb(char *nom,int tok){
  int i;
  for (i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token=tok;
  if (tok==ID) {  /*
  	printf("Parece que es un ID .... \n");
  	cout << "Tenemos... " << tok << "\n"; 
	cout << "TablaSim[nSim].nombre = **  " << TablaSim[nSim].nombre << " ** esto\n";*/
	TablaSim[nSim].valor=0.0;
	}
  if (tok==NUM) {  
  	sscanf(nom,"%lf",&TablaSim[nSim].valor);
	}
 	 nSim++;
  return nSim-1;
}



void yyerror(char *msg){
  printf("ERROR:%s \n",msg);
}



void actualiza(){
	
	string name_function;
	int i,a1,a2,a3,op,j,temp;
	if(VERBOSE_ACTUALIZA) printf("######## cx = %d ######\n",cx);

	for( i=0; i<=cx; i++ ){

		if(VERBOSE_ACTUALIZA) printf("******* Iteracion %d \n: ********",i);
		op = TCodigo[i].op;
		a1 = TCodigo[i].a1;
		a2 = TCodigo[i].a2;
		a3 = TCodigo[i].a3;

        if(VERBOSE_ACTUALIZA) cout << "operacion : " << operaName[op] << " " << TablaSim[a1].nombre << " " << TablaSim[a2].nombre << " " << TablaSim[a3].nombre << endl;

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
			if (TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}
		if(op==IGUAL){
			if (abs(TablaSim[a2].valor-TablaSim[a3].valor) < 0.0001) TablaSim[a1].valor=1;
			else
				TablaSim[a1].valor=0;
		}

		if(op==SUMAR){
			TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
		}
		if(op==RESTAR){TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;}
        if(op==MODULO){TablaSim[a1].valor = fmod(round(TablaSim[a2].valor), round(TablaSim[a3].valor));}
		//if(op==MODULO){TablaSim[a1].valor = (int) round(TablaSim[a2].valor) % (int) round(TablaSim[a3].valor);}
		if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
		if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
		if(op==RAIZ) TablaSim[a1].valor = sqrt(TablaSim[a2].valor);
		if(op==POT) TablaSim[a1].valor = pow(TablaSim[a2].valor, TablaSim[a3].valor);
		if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;

		if(op==SALTARF1){
			printf("Bloque if, SALTARF1\n");
			printf("a1=%d a2=%d TablaSim[a1].valor=%f\n",a1,a2,TablaSim[a1].valor);

        	if(TablaSim[a1].valor==0){printf("En saltar f1, la condicion no se cumplio"); i=a2-1;printf("i es %d , a2 es %d \n",i,a2); };
        	printf("##Ahora i vale %d ##\n",i);
    		printf("La siguiente operacion: %d\n",TCodigo[i+1].op);
		}
		if(op==SALTARF2){ 
			i=a1-1;
			printf("##### SALTARF2 ahora i vale %d \n #####",i);
		}
		if(op==SALTARF3){
			if(!bucle_activado[cotas[i]])
				cotas.insert({i, cotaI});
				asignar_cotas(a1,a2);
				cotaI++;
			bucle_activado[cotas[i]] = 1;
			if(cota_inferior[cotas[i]] <= cota_superior[cotas[i]]){
				cota_inferior[cotas[i]]++;	
			}
			else{
				bucle_activado[cotas[i]] = 0;
				i = a3 - 1;
			}
		}
		if(op==BUCLE) {
			if(bucle_activado[cotas[i]]){
				i = a2-1;
			}
			else{
				i = a1-1;
			}
		}

		if(op==SALTARF4){
			if(whileMap.size() == 0) whileMap.insert({i, whileI++});
			if(whileMap.insert({i, whileI}).second == true) whileI++;
			
			while_activado[whileMap[i]]=1;
			if(TablaSim[a1].valor==0){while_activado[whileMap[i]]=0;i = a2-1;}
		}
		if(op==WHILE){
			if(while_activado[whileMap[a2]]){
				i = a2-2;
			}
		}

if(op==POSFUNCION){

			i = a2;
		}

		if(op==LLAMADAFUNC){
			name_function = llamada_info[i];
			current_function = llamada_info[i];
			funciones_posiciones[name_function][2] = i;

			i = funciones_posiciones[name_function][0];
		}

		if(op==SALIRFUNCION){
			i = funciones_posiciones[current_function][2];
		}


		if(op==ASIGNAR) {
			if(VERBOSE){
				printf("Se procedera con la asignacion...\n");
				printf("op es %d a1 es %d a2 es %d a3 es %d\n",op,a1,a2,a3);
				printf("TablaSim[a1].valor sera TablaSim[a2].valor, que es %f\n", TablaSim[a2].valor);
				}
			TablaSim[a1].valor = TablaSim[a2].valor;
		}

		if(op==IMPRIMIR) {
			printf("# %F\n", TablaSim[a1].valor);
		}

		if(VERBOSE_ACTUALIZA) printf("tabla de simbolos antes de actualizarse\n");
		if(VERBOSE_ACTUALIZA) imprimeTablaSim();

		if(VERBOSE_ACTUALIZA) printf("********************************\n\n");

	}

	/*
	for(auto k : whileMap) {
		printf("---- i : %d  whileI : %d\n", k.first, k.second);
	}
	*/

}


int main(int argc, char *argv[]) {
	if(argc > 1 && argv[1][0] == '-') {
		for(int i = 1; argv[1][i] != '\0'; i++) {
			if(argv[1][i] == 'A') VERBOSE_ACTUALIZA = 1;
			if(argv[1][i] == 'V') VERBOSE = 1;
		}
		
	} 

	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
	//printf("tabla de codigos\n");
	/*		imprimeTablaCod();

	printf("tabla de simbolos antes de actualizarse\n");
	imprimeTablaSim();	
	printf("*********************");
	*/
	actualiza();
	printf("tabla de codigos\n");
	imprimeTablaCod();
	printf("tabla de simbolos\n");
	imprimeTablaSim();
	
    
	return 0;
}





