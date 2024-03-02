#!/bin/bash

gcc -Wall -Werror --pedantic main.c -o main -std=c99 -I ./raylib/src -L ./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

