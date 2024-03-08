#include "game.h"
#include "raylib.h"

void InitializeGame(Game* game) {
    game -> status = START;
}

void clickToStart(Game* game) {
    if(GetKeyPressed()) 
        game -> status = GAMEPLAY;
}

void restartOrExit(Game* game) {
    if(IsKeyDown(KEY_R)) {
        game -> status = START;
    } 
    if(GetKeyPressed()) {
        game -> status = END;
    }
}
