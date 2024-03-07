#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "raylib.h"

typedef struct {
	bool jump;
} Action;

typedef struct {
	int framesCounter;
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
void setAnimationPosition(AnimationData* animation, Vector2 position);

void walkAnimation(Texture2D* sprite, AnimationData* animation);
void jumpAnimation(Texture2D* sprite, AnimationData* animation);
void moveBackward(Texture2D* sprite, AnimationData* animation);


bool detectCollitions(Rectangle p1, Rectangle p2);
void initBackground(Background* back, Background* mid, Background* fore);
void moveBackground(Background* back, Background* mid, Background* fore, int backgroundWidth, int midgroundWidth, int foregroundWidth);
void RenderBackground(Texture2D* background,Texture2D* midground, Texture2D* foreground, Background* back, Background* mid, Background* fore);
#endif
