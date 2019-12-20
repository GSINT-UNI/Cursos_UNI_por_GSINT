#!/bin/bash

bison tabla.ypp -v 
g++ -std=c++14 -w tabla.tab.cpp -lm -o prog

./prog < input.txt
