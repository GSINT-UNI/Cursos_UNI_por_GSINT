#!/bin/bash

bison $1.y
gcc $1.tab.c -lm

./a.out < input.txt
