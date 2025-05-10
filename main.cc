/*A simple yaycaster engine using raylib
Copyright (C) 2025 Julian Franko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see https://www.gnu.org/licenses.*/

#include "raylib.h"

float px, py;
int mapX=8, mapY=8, mapS=64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void drawPlayer(float posX, float posY) {
    DrawPixel(posX, posY, YELLOW);
}

void drawMap2d() {
    for (int y = 0; y < mapY; y++)
    {
        for (int x = 0; x < mapX; x++)
        {
            Color wColor;
            if (map[y*mapX+x]==1){wColor = WHITE;}else{wColor = BLACK;}
            DrawRectangle(x*64, y*64, mapS, mapS, wColor);
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
    const int screenWidth = 512;
    const int screenHeight = 512;

    px = screenWidth/2; py = screenHeight/2;

    InitWindow(screenWidth, screenHeight, "Divine Intellect Raycaster");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // Update your variables here
        movePlayer();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            drawMap2d();
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
