#!/bin/bash

exe_path="./build-linux/*"

if [ -e "$exe_path" ]; then
    rm -f "$exe_path"
fi

gcc -Wall -Werror --pedantic ./src/main.c ./src/animations.c ./src/game.c -o ./build-linux/debug -std=c99 -I ./raylib/src -L ./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./build-linux/debug
