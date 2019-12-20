#!/bin/bash

bison -vd tabla.y
flex -l flex_file.l
g++ -std=c++14 -w lex.yy.c tabla.tab.c -ll -o prog
