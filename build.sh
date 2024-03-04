#!/bin/bash

exe_path="./main"

if [ -e "$exe_path" ]; then
    rm -f "$exe_path"
fi

rm ./main

gcc -Wall -Werror --pedantic main.c animations.c -o main -std=c99 -I ./raylib/src -L ./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./main
