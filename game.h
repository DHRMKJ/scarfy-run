#ifndef GAME_H
#define GAME_H
#include "config.h"

typedef enum {
	START,
	GAMEPLAY,
	END
} Screen;


typedef struct {
	Screen status;
} Game;

void InitializeGame(Game* game);

#endif
