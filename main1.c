#include "raylib.h"
#define FPS 60
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define BACKGROUND_TEXTURE 0.0f, 2.0f, WHITE
#define MAX_SPRITE_FRAMES 5
#define SPRITES_COUNTER 6
typedef struct {
	int currentFrame;
	int framesSpeed;
	Vector2 position;
	Rectangle frameRec;
} AnimationData;

void initAnimationData(AnimationData* animation, Texture2d* sprite) {
	animation -> framesCounter = 0;
	animation -> currentFrame = 0;
	animation -> framesSpeed = 8;
	animation -> position = {sprite->width/SPRITES_COUNTER, SCREEN_HEIGHT - sprite -> height};
	animation -> frameRec = { 0.0f, 0.0f, (float)sprite -> width/SPRITE_COUNTER, (float)sprite -> height };
}


//void walk_animation(Texture2D* sprite, int* framesCounter, int* framesSpeed, int* currentFrame,

int main(void)
{
    InitWindow(screenWidth, screenHeight, "scarfy run");
    int framesCounter = 0;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/scarfy.png");        // Texture loading
    //Texture2D fatass = LoadTexture("resources/character_tribe_spritesheet.png");	
    Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");    

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
	
    float backScrollSpeed = 0.1f;
    float midScrollSpeed = 0.5f;
    float foreScrollSpeed = 1.0f;

    int jumpFlag = 0;
    AnimationData scarfyAnimation;
    initAnimationData(&scarfyAnimation, &scarfy);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;

        if (framesCounter >= (FPS / scarfyAnimation.framesSpeed))
        {
            framesCounter = 0;
            scarfyAnimation.currentFrame++;

            if (scarfyAnimation.currentFrame > MAX_SPRITE_FRAMES) scarfyAnimation.currentFrame = 0;

            scarfyAnimation.frameRec.x = (float)scarfyAnimation.currentFrame * (float)scarfy.width/6;
        }
	
	if(!jumpFlag && IsKeyDown(KEY_UP)) {
		if(scarfyAnimation.position.y >= 140) {
			scarfyAnimation.position.y -= 10.0;
		}
		else {
			jumpFlag = true;
		}
	}

	if(IsKeyReleased(KEY_UP)) {
		jumpFlag = true;
	}
	
	if(jumpFlag) {
		if(scarfyAnimation.position.y != SCREEN_HEIGHT - scarfy.height) {
			position.y += 10.0;
		}else {
			jumpFlag = false;
		}
	}

        scrollingBack -= backScrollSpeed;
        scrollingMid -= midScrollSpeed;
        scrollingFore -= foreScrollSpeed;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;

	BeginDrawing();
	    ClearBackground(GetColor(0x052c46ff));

            DrawTextureEx(background, (Vector2){scrollingBack, 20}, BACKGROUND_TEXTURE);
            DrawTextureEx(background, (Vector2){background.width*2 + scrollingBack, 20}, BACKGROUND_TEXTURE);

            DrawTextureEx(midground, (Vector2){scrollingMid, 20}, BACKGROUND_TEXTURE);
            DrawTextureEx(midground, (Vector2){midground.width*2 + scrollingMid, 20}, BACKGROUND_TEXTURE);

            DrawTextureEx(foreground, (Vector2){scrollingFore, 70}, BACKGROUND_TEXTURE);
            DrawTextureEx(foreground, (Vector2){foreground.width*2 + scrollingFore, 70}, BACKGROUND_TEXTURE);
	
	    //DrawTextureRec(fatass, fatassRec, fatassPos, WHITE);
            DrawTextureRec(scarfy, scarfyAnimation.frameRec, scarfyAnimation.position, WHITE);  // Draw part of the texture

        EndDrawing();
    }
    UnloadTexture(scarfy);      // Texture unloading
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground); 
 
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
