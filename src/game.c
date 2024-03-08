#include "game.h"
#include "raylib.h"
#include <stdio.h>
void InitializeGame(Game* game) {
    game -> status = START;
}

void clickToStart(Game* game) {
    if(GetKeyPressed()) 
        game -> status = GAMEPLAY;
}

void restartOrExit(Game* game) {
    if(IsKeyDown(KEY_R)) {
        printf("SHIT");
        game -> status = START;
    } 
    if(GetKeyPressed()) {
        game -> status = END;
    }
}
