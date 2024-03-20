#ifndef GAME_H
#define GAME_H
#include <time.h>

typedef enum {
	START,
	GAMEPLAY,
	END
} Screen;

typedef struct {
	Screen status;
	time_t started_at;
	char* score;
} Game;

void InitializeGame(Game* game);
void clickToStart(Game* game);
void restartOrExit(Game* game);
void calcScore(Game* game);
void cleanUpMemory(Game* game);

#endif
