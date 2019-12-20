#!/bin/bash
prog="demo2.y"
bison $prog
foo="$foo.tab.c"
gcc $foo
./a.out

