#include "config.h"
#include "animations.h"

void initAnimationData(AnimationData* animation, Texture2D* sprite) {
	animation -> currentFrame = 0;
	animation -> framesSpeed = 8;
	animation -> position.x =  sprite->width/SPRITES_COUNTER;
	animation -> position.y = SCREEN_HEIGHT - sprite -> height;
	animation -> frameRec.x =  0.0f;
	animation -> frameRec.y = 0.0f;
	animation -> frameRec.width = (float)sprite -> width/SPRITES_COUNTER;
	animation -> frameRec.height = (float)sprite -> height;
	animation -> actions.jump = false;
}

void walkAnimation(int* framesCounter, Texture2D* sprite, AnimationData* animation) {
        if (*framesCounter >= (FPS / animation -> framesSpeed)) {
            *framesCounter = 0;
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
			animation-> actions.jump = true;
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
	back -> speed = 0.1f;
	back -> scroll = 0.0f;
	
	mid -> speed = 0.5f;
	mid -> scroll = 0.0f;
	
	fore -> speed = 1.0f;
	fore -> scroll = 0.0f;
}


void moveBackground(Background* back, Background* mid, Background* fore, int width) {
	back -> scroll -= back -> speed;
	mid -> scroll -= mid -> speed;
	fore -> scroll -= fore -> speed;
        if (back -> scroll <= -width*2) back -> scroll = 0;
        if (mid -> scroll <= -width*2) mid -> scroll = 0;
        if (fore -> scroll <= -width*2) fore -> scroll = 0;
}
