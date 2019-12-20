%{
  #include <cstdio>
  #include <iostream>
  using namespace std;

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
 
  void yyerror(const char *s);
%}

%union {
  int ival;
  float fval;
  char *sval;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
snazzle:
  snazzle INT {
      cout << "bison found an int: " << $2 << endl;
    }
  | snazzle FLOAT {
      cout << "bison found a float: " << $2 << endl;
    }
  | snazzle STRING {
      cout << "bison found a string: " << $2 << endl; free($2);
    }
  | INT {
      cout << "bison found an int: " << $1 << endl;
    }
  | FLOAT {
      cout << "bison found a float: " << $1 << endl;
    }
  | STRING {
      cout << "bison found a string: " << $1 << endl; free($1);
    }
  ;
%%

int main(int, char**) {
  // open a file handle to a particular file:
  FILE *myfile = fopen("a.snazzle.file", "r");
  // make sure it is valid:
  if (!myfile) {
    cout << "I can't open a.snazzle.file!" << endl;
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // Parse through the input:
  yyparse();
}

void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}