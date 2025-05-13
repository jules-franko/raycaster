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
#include <math.h>
#include <iostream>

const int screenWidth = 512;
const int screenHeight = 512;

float px, py;
float pa = 0;
float pdx, pdy;
float FOV = 50*PI/180;
float num_rays = 512;

int mapX=8, mapY=8, mapS=64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void drawPlayer() {
    DrawPixel(px, py, YELLOW);
}

void drawRays() {
    float ray_end_x = px + 512 * pdx;
    float ray_end_y = py + 512 * pdy;

    DrawLine(px, py, ray_end_x, ray_end_y, GREEN);
}

// void drawRaysBad()
// {
//
//     float angle_incr = FOV / num_rays;
//     float start_angle = pa - (FOV/2);
//
//     float sim_angle = 0;
//     int len;
//     bool hit = false;
//
//     //Loops for the amount of rays to draw
//     for (int j = 0; j < num_rays; j++)
//     {
//         sim_angle = start_angle + j * angle_incr;
//
//         //Draws a single line at angle
//         for (int i = 0; i < 512; i++)
//         {
//             float lx = px + i * cos(sim_angle);
//             float ly = py + i * sin(sim_angle);
//             DrawPixel(lx, ly, GREEN);
//             int y = int(ly/64);
//             int x = int(lx/64);
//
//             if ((map[  x  ] == 1) && (map[ y*8+x ]))
//             {
//                 hit = true;
//                 len = i;
//                 break;
//             }
//         }
//
//         len *= cos(pa - sim_angle);
//         int len2 = 512-len;
//
//         if (hit)
//         {
//             DrawLine(j, len2/2, j, len2+(len2/2), RED);
//         }
//
//     }
//
//
// }

void drawRays3D()
{
    float fov = 50*PI/180;
    float num_rays = 512;
    float start_angle = pa - (fov/2);
    float angle = 0;
    float len;
    float render_len;

    //Draw for entire fov
    for (int j = 0; j < num_rays; j++)
    {
        angle = start_angle + j * (fov/num_rays);

        //Draw one line
        for (int i =0; i < 512; i++)
        {
            float lx = px + i * cos(angle);
            float ly = py + i * sin(angle);
            DrawPixel(lx, ly, GREEN);

            //Get the (x,y) of the newest point
            int y = int(ly/64);
            int x = int(lx/64);

            if ((map[  x  ] == 1) && (map[ y*8+x ]))
            {
                len = i;
                render_len = 512 - len;
                break;
            }
        }

        //Fix the fisheye?
        render_len = render_len* cos(pa - angle);
        if (render_len > 320) (render_len = 320);

        //Draw the rendered line
        DrawRectangle(j*(512/num_rays), render_len/2, (512/num_rays), render_len, RED);
    }
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

    if (IsKeyDown(KEY_W)) {
        px += 1*cos(pa);
        py += 1*sin(pa);
    }
    if (IsKeyDown(KEY_S)) {
        px -= 1*cos(pa);
        py -= 1*sin(pa);
    }

    if (IsKeyDown(KEY_D)) {
        pa += 0.01;
        if (pa >= 2*PI) {
            pa = 0;
        }
    }
    if (IsKeyDown(KEY_A)) {
        pa -= 0.01;
        if (pa <= 0) {
            pa = 2*PI;
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    px = screenWidth/2;
    py = screenHeight/2;
    pdx = cos(pa);
    pdy = sin(pa);

    InitWindow(screenWidth, screenHeight, "Divine Intellect Raycaster");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // Update your variables here
        movePlayer();
        pdx = cos(pa);
        pdy = sin(pa);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            drawMap2d();
            drawPlayer();
            drawRays3D();
            //drawRays();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
