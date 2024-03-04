#include "config.h"
#include "animations.h"

void setAnimationPosition(AnimationData* animation, Vector2 position) {
	animation -> position = position;
}

void initAnimationData(AnimationData* animation, Texture2D* sprite) {
	animation -> currentFrame = 0;
	animation -> framesSpeed = 8;
	animation -> position.x =  sprite->width / SPRITES_COUNTER;
	animation -> position.y = SCREEN_HEIGHT - sprite -> height;
	animation -> frameRec.x =  0.0f;
	animation -> frameRec.y = 0.0f;
	animation -> frameRec.width = (float)sprite -> width/SPRITES_COUNTER;
	animation -> frameRec.height = (float)sprite -> height;
	animation -> actions.jump = false;
}

void walkAnimation(Texture2D* sprite, AnimationData* animation) {
        if (animation -> framesCounter >= (FPS / animation -> framesSpeed)) {
            animation -> framesCounter = 0;
            animation -> currentFrame++;
	    if (animation -> currentFrame > MAX_SPRITE_FRAMES) { 
		    animation -> currentFrame = 0;
	    } 
	    animation -> frameRec.x = (float)animation -> currentFrame * (float)sprite -> width / SPRITES_COUNTER;
        }
}

void jumpAnimation(Texture2D* sprite, AnimationData* animation) {
	const int MAX_JUMP = 140;
	const float GRAVITY = 10.0;
	if(!animation -> actions.jump && IsKeyDown(KEY_UP)) {
		if (animation -> position.y >= MAX_JUMP) {
			animation -> position.y -= GRAVITY;
		}
		else {
			animation -> actions.jump = true;
		}
	}

	if(IsKeyReleased(KEY_UP)) {
		animation -> actions.jump = true;
	}
	
	if(animation -> actions.jump) {
		if(animation -> position.y != SCREEN_HEIGHT - sprite -> height) {
			animation -> position.y += GRAVITY;
		}else {
			animation -> actions.jump = false;
		}
	}
}

void initBackground(Background* back, Background* mid, Background* fore) {
	back -> speed = SPEED / 10;
	back -> scroll = 0.0f;
	
	mid -> speed = SPEED / 2;
	mid -> scroll = 0.0f;
	
	fore -> speed = SPEED;
	fore -> scroll = 0.0f;
}


void moveBackground(Background* back, Background* mid, Background* fore, int backgroundWidth, int midgroundWidth, int foregroundWidth) {
	back -> scroll -= back -> speed;
	mid -> scroll -= mid -> speed;
	fore -> scroll -= fore -> speed;
        if (back -> scroll <= -backgroundWidth*2) back -> scroll = 0.0f;
        if (mid -> scroll <= -midgroundWidth*2) mid -> scroll = 0.0f;
        if (fore -> scroll <= -foregroundWidth*2) fore -> scroll = 0.0f;
}
