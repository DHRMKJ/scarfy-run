#include "config.h"
#include "animations.h"

void RenderBackground(Texture2D* background,Texture2D* midground, Texture2D* foreground, Background* back, Background* mid, Background* fore) {
	    DrawTextureEx(*background, (Vector2){back -> scroll, 20}, BACKGROUND_TEXTURE);
            DrawTextureEx(*background, (Vector2){background -> width*2 + back -> scroll, 20}, BACKGROUND_TEXTURE);

            DrawTextureEx(*midground, (Vector2){mid -> scroll, 20}, BACKGROUND_TEXTURE);
            DrawTextureEx(*midground, (Vector2){midground -> width*2 + mid -> scroll, 20}, BACKGROUND_TEXTURE);

            DrawTextureEx(*foreground, (Vector2){fore -> scroll, 70}, BACKGROUND_TEXTURE);
            DrawTextureEx(*foreground, (Vector2){foreground -> width*2 + fore -> scroll, 70}, BACKGROUND_TEXTURE);
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "scarfy run");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/scarfy.png");        // Texture loading
    Texture2D caveguy = LoadTexture("resources/attack.png");

    Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");    

    Background back, mid, fore;
    initBackground(&back, &mid, &fore);
    
    AnimationData scarfyAnimation;
    initAnimationData(&scarfyAnimation, &scarfy);

    AnimationData caveguyAnimation;
    initAnimationData(&caveguyAnimation, &caveguy);
    setAnimationPosition(&caveguyAnimation, (Vector2){ SCREEN_WIDTH, SCREEN_HEIGHT - caveguy.height });	

    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        scarfyAnimation.framesCounter += 1;
	caveguyAnimation.framesCounter += 1;
	
	walkAnimation(&caveguy, &caveguyAnimation);

	walkAnimation(&scarfy, &scarfyAnimation);
	jumpAnimation(&scarfy, &scarfyAnimation);

	if(caveguyAnimation.position.x + caveguy.width/SPRITES_COUNTER >= 0) { 
		setAnimationPosition(&caveguyAnimation, (Vector2){ caveguyAnimation.position.x - SPEED, caveguyAnimation.position.y});
	}
	else {
 		setAnimationPosition(&caveguyAnimation, (Vector2){ SCREEN_WIDTH, SCREEN_HEIGHT - caveguy.height });
	}
	moveBackground(&back, &mid, &fore, background.width, midground.width, foreground.width);
	// NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
	BeginDrawing();
	    ClearBackground(GetColor(0x052c46ff));
	    RenderBackground(&background, &midground, &foreground, &back, &mid, &fore);    
	    DrawTextureRec(caveguy, caveguyAnimation.frameRec, caveguyAnimation.position, WHITE);
	    DrawTextureRec(scarfy, scarfyAnimation.frameRec, scarfyAnimation.position, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);      // Texture unloading
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground); 
 
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
