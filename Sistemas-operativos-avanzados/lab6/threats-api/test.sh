#!/bin/bash

function echoerr() { 
    echo "$@" 1>&2
}

if [ "$#" -eq "2" ]; then
    times=`seq $2 2>/dev/null || (echoerr "Error. Check your input" && kill -9 $$)` 
    for i in $times; do
        ./$1
    done 
else
    echoerr "Usage: $0 <program> <times2test>"
fi