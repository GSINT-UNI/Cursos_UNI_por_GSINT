%{
//incluimos librerias y cabeceras
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
char lexema[64];
void yyerror(char *);
int yylex();
%}

%token ID NUM POT RAIZ SI SINO MIENTRAS END ASCII UNION INTERSECCION TIPO PARA DESDE HASTA PUNTCOM COMENTARIO

%%


/*---------------------------------------------------
                ESTRUCTURA DEL COMPILADOR     
-----------------------------------------------------*/

programa: estructura;

estructura: estructura comentario
        | estructura ifelse 
        | estructura while 
        | estructura for 
        | estructura asignacion 
        | estructura declaracion 
        | ;


declaracion: ID '=' expresion '('TIPO')' PUNTCOM;

asignacion: ID '=' expresion PUNTCOM;
        
        
/*---------------------------------------------------
                 OPERACIONES BASICA     
-----------------------------------------------------*/

expresion: expresion '+' producto           { $$ = $1 + $3; }
        | expresion '-' producto            { $$ = $1 - $3; }
        | producto ;

producto: producto '*' agrupacion           { $$ = $1 * $3; }
        | producto '/' agrupacion           { $$ = $1 / $3; }
        | agrupacion ;
        
// Deginimos raiz y potencia

agrupacion: RAIZ '(' expresion ')'             { $$ = sqrt($3); } 
       | POT '(' expresion ',' expresion ')'   { $$ = pow($3,$5); }
       | '(' expresion ')' 
       | valor;


/*
EL COMPILADOR ACEPTA VALORES NUMERICOS, VARIABLES, ejm : x, 5 , (-3) , etc
*/

valor: NUM 
      | ID 
      | '(' '-' NUM ')';
 
/*---------------------------------------------------
                 OPERACIONES SELECTIVAS    
-----------------------------------------------------*/

// DEFINO IFELSE  

ifelse: SI '(' list_cond ')' ':' estructura  
   SINO ifelse 
      | SI '(' list_cond ')' ':' estructura END ;
        

// LISTA DE CONDICIONES 

list_cond: condicion
        | condicion UNION list_cond      //  interseccion
        | condicion INTERSECCION list_cond      //  union
        | ;

condicion: expresion orden expresion ;

// OPERADORES DE COMPARACION (<,>,=,!)  

orden: '>'                 // mayor
        | '>''='             // mayor igual
        | '<'                 // menor
        | '<''='             // menor igual
        | '=''='             // igual
        | '!''=' ;            // diferente
        

// DEFINO FOR     
for: PARA '(' asignacion condicion PUNTCOM contador ')' ':' estructura END | PARA ID DESDE NUM HASTA NUM ':' estructura END;

contador: ID '=' expresion ;

//DEFINO WHILE
while: MIENTRAS '(' list_cond ')' ':' estructura END ;

//HABILIDAD PARA AGREGAR COMENTARIO CON LA FORMA: # comentario $
comentario: COMENTARIO ;

//agrego esto para que los comentarios puedan tener cualquier palabra incluso las instruc ciones.

%% 
// AQUI GUARDO TODAS LAS PALABRAS QUE VOY A USAR PARA LLAMAR INSTRUCCIONES

int palabras( char lexema[] ) {
    //   Selectivas
    if( strcmp( lexema, "si" ) == 0 ) return SI;
    if( strcmp( lexema, "sino" ) == 0 ) return SINO;
     //   Repetitivas
    if( strcmp( lexema, "para" ) == 0 ) return PARA;
    if( strcmp( lexema, "mientras" ) == 0 ) return MIENTRAS;
     //   Fin estructuras
   if( strcmp( lexema, "end" ) == 0 ) return END;
     //   Operaciones
    if( strcmp( lexema, "raiz" ) == 0 ) return RAIZ;
        if( strcmp( lexema, "para" ) == 0 ) return PARA;

    if( strcmp( lexema, "desde" ) == 0 ) return DESDE;

    if( strcmp( lexema, "hasta" ) == 0 ) return HASTA;

    if( strcmp( lexema, "pot" ) == 0 ) return POT;
    if( strcmp( lexema, "oo" ) == 0 ) return UNION;
    if( strcmp( lexema, "yy" ) == 0 ) return INTERSECCION;
    if( strcmp( lexema, "entero" ) == 0 || strcmp( lexema, "real" ) == 0) return TIPO;

    return ID;
}



//codigo, scanner, parser

void yyerror(char *mgs){
    printf("error: %s", mgs);
}

int yylex(){ 
/*esto retorna un token es decir numeros analizador lexico hecho a mano */

    char c;
    while(1){
        c=getchar();
        if(c=='\n') continue;

        if(c=='#') {
            int i = 0;
            do {
                lexema[i++] = c;
                c = getchar();
            } while(c!='$');
            lexema[i] = c;
            return COMENTARIO;
        }

        if(isspace(c)) continue;        
        if(c==';') return PUNTCOM;        
                
        if(isalpha(c)) {    //verifica si es un caracter
            int i=0;
            do {
                lexema[i++]=c;
                c=getchar();
            }while(isalnum(c));
            
            ungetc(c,stdin);    //devuelve el caracter a la entrada estandar
        lexema[i]=0;
        return palabras(lexema); //devuelve una palabra reservada
        }
        
        	if(isdigit(c)){//verifica si es un nro. entero
			int i=0;
			int decimalFlag = 0;
			int decimal_detectado=0;
			do{
			    if (decimalFlag){decimal_detectado = 1;}
				lexema[i++]=c;
				c=getchar();
				if( c == '.' ){decimalFlag = 1;}
			}while(isdigit(c) || (( c == '.' )&&(!decimal_detectado)) );
		ungetc(c,stdin);//devuelve el caracter a la entrada estandar
		lexema[i]=0;
		return NUM; //devuelve el token
		}
        
        return c;
    }
}

void main(){
/* Llamar al scaner o analizador lexico esto lo inicia el parser o analizador sintactico */
//yyparse

    if(!yyparse())
        printf("cadena es valida\n");
    else
        printf("cadena invalida\n");
}


