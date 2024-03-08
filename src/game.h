#ifndef GAME_H
#define GAME_H

typedef enum {
	START,
	GAMEPLAY,
	END
} Screen;

typedef struct {
	Screen status;
} Game;

void InitializeGame(Game* game);
void clickToStart(Game* game);
void restartOrExit(Game* game);

#endif
