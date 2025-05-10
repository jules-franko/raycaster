#include "raylib.h"

float px, py;

int mapX=8, mapY=8, mapS=64;
int map[] =
{
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
};

void drawPlayer(float posX, float posY) {
    DrawPixel(posX, posY, YELLOW);
}

void drawMap2d() {
    for (int y = 0; y < mapY; y++)
    {
        for (int x = 0; x < mapX; x++)
        {
            if (map[y*mapX+x]==1) {} else {};

        }
    }
}

void movePlayer() {

    if (IsKeyDown(KEY_D)) px++;
    if (IsKeyDown(KEY_A)) px--;
    if (IsKeyDown(KEY_W)) py--;
    if (IsKeyDown(KEY_S)) py++;

}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;

    px = screenWidth/2; py = screenHeight/2;

    InitWindow(screenWidth, screenHeight, "Divine Intellect Raycaster");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        movePlayer();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            drawPlayer(px, py);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
