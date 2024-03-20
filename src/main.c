#include <string.h>
#include "config.h"
#include "animations.h"
#include "game.h"

int main(void)
{
    Game game;
    InitializeGame(&game); 
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
    AnimationData caveguyAnimation;

    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch(game.status) {
            case START:
                initAnimationData(&scarfyAnimation, &scarfy);
                initAnimationData(&caveguyAnimation, &caveguy);
                setAnimationPosition(&caveguyAnimation, (Vector2){ SCREEN_WIDTH, SCREEN_HEIGHT - caveguy.height });	
                clickToStart(&game);
                break;
            case GAMEPLAY:
        	    scarfyAnimation.framesCounter += 1;
	            caveguyAnimation.framesCounter += 1;
                calcScore(&game);
	            walkAnimation(&caveguy, &caveguyAnimation);
	            moveBackward(&caveguy, &caveguyAnimation);

	            walkAnimation(&scarfy, &scarfyAnimation);
	            jumpAnimation(&scarfy, &scarfyAnimation);

                Rectangle scarfyPosition = { scarfyAnimation.position.x, scarfyAnimation.position.y, scarfy.width / SPRITES_COUNTER, scarfy.height };     
                Rectangle caveguyPosition = { caveguyAnimation.position.x, caveguyAnimation.position.y, caveguy.width / SPRITES_COUNTER, caveguy.height };
                if(detectCollitions(scarfyPosition, caveguyPosition)) {                                                                                   
                	game.status = END;                                                                                                                             
                }                                                                                                                                         
                break;
            case END:
                restartOrExit(&game);
                break;
        }

        moveBackground(&back, &mid, &fore, background.width, midground.width, foreground.width);                                                  
	    // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
	    BeginDrawing();
	    ClearBackground(GetColor(0x052c46ff));
	    RenderBackground(&background, &midground, &foreground, &back, &mid, &fore);            
        switch(game.status) {
        	case START:
                DrawText("PRESS ANY KEY TO START", SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 50, 20, WHITE);
                break;
            case GAMEPLAY:
                DrawText(game.score, SCREEN_WIDTH - 20 * strlen(game.score) - 20 , 20, 40, WHITE);
	        	DrawTextureRec(caveguy, caveguyAnimation.frameRec, caveguyAnimation.position, WHITE);
	            DrawTextureRec(scarfy, scarfyAnimation.frameRec, scarfyAnimation.position, WHITE);
	            break;
	        case END:
	            DrawText("PRESS [R] to restart / any other key to exit", SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 50, 20, WHITE);   
	            break; 
        }
	    EndDrawing();
    }
    UnloadTexture(scarfy);      // Texture unloading
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground); 
    cleanUpMemory(&game);
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
