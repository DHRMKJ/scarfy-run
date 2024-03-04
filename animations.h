#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "raylib.h"

typedef struct {
	bool jump;
} Action;

typedef struct {
	int currentFrame;
	int framesSpeed;
	Vector2 position;
	Rectangle frameRec;
	Action actions;
} AnimationData;

typedef struct {
	float speed;
	float scroll;
} Background;

void initAnimationData(AnimationData* animation, Texture2D* sprite); 
void walkAnimation(int* framesCounter, Texture2D* sprite, AnimationData* animation);
void jumpAnimation(Texture2D* sprite, AnimationData* animation);
void initBackground(Background* back, Background* mid, Background* fore);
void moveBackground(Background* back, Background* mid, Background* fore, int width);
#endif
