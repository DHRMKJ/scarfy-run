#include "raylib.h"
#define BACKGROUND_TEXTURE 0.0f, 2.0f, WHITE

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "scarfy run");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/scarfy.png");        // Texture loading
    Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");    

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
	
    float backScrollSpeed = 0.1f;
    float midScrollSpeed = 0.5f;
    float foreScrollSpeed = 1.0f;

    Vector2 position = { scarfy.width/6, screenHeight - scarfy.height};
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second

    int jumpFlag = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)scarfy.width/6;
        }
	
	if(!jumpFlag && IsKeyDown(KEY_UP)) {
		if(position.y >= 140) {
			position.y -= 10.0;
		}
		else {
			jumpFlag = true;
		}
	}

	if(IsKeyReleased(KEY_UP)) {
		jumpFlag = true;
	}
	
	if(jumpFlag) {
		if(position.y != screenHeight - scarfy.height) {
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

            DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture

        EndDrawing();
    }
    UnloadTexture(scarfy);      // Texture unloading
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground); 
 
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
