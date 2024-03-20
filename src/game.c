#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "game.h"
#include "raylib.h"
#define SCORE_BUFFER 40


void InitializeGame(Game* game) {
    game -> status = START;
    time_t time_now = time(NULL);
    if(time_now != (time_t)(-1)) {
        game -> started_at = time_now;
    }
    game -> score = (char*)malloc(sizeof(char) * SCORE_BUFFER);
    game -> score[0] = '0';
}

void clickToStart(Game* game) {
    if(GetKeyPressed()) 
        game -> status = GAMEPLAY;
}

void restartOrExit(Game* game) {
    int key_pressed_rn = GetKeyPressed(); 
    printf("Key %d", key_pressed_rn);
    switch (key_pressed_rn) {
       case 0:
            break;
       case 344:
            break;
       case KEY_R:
            cleanUpMemory(game);
            InitializeGame(game);
            break;
       case KEY_ENTER:
            cleanUpMemory(game);
            InitializeGame(game);
            break;
       default:
            cleanUpMemory(game);
            exit(1);
    }
}

void calcScore(Game* game) {
    time_t time_now = time(NULL);
    if(time_now != (time_t)(-1)) {
        long long time_elapsed = ((long long)time_now - (long long)game -> started_at);
        sprintf(game -> score, "%lld", time_elapsed);
    }
}

void cleanUpMemory(Game* game) {
    if(game -> score != NULL)
        free(game -> score);
}

