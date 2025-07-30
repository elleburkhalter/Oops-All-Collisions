
// This is the program that will build with --DWITH_SFML=ON and
// run with --visualize=1
/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "game_object/interfaces/EntityABC.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 2500;
    const int screenHeight = 1500;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    SetTargetFPS(60);    // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    bool onWelcomeScreen = true;

    EntityABC exampleGuy1(screenWidth/2, screenHeight/2, 10);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (onWelcomeScreen) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                onWelcomeScreen = false;
            }
        }
        //----------------------------------------------------------------------------------
        else {
            exampleGuy1.playerControl();
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        if (onWelcomeScreen)
        {
            DrawText("Oops! All Collisions",(screenWidth - MeasureText("Oops! All Collisions", 120)) / 2,screenHeight / 2 - 250,120, BLUE);
            DrawText("Created by Logan Dapp, Derrick Davison, and Elle Burkhalter",(screenWidth - MeasureText("Created by Logan Dapp, Derrick Davison, and Elle Burkhalter", 50)) / 2,screenHeight / 2 - 120, 50, GREEN);
            DrawText("Click anywhere to begin...",(screenWidth - MeasureText("Click anywhere to begin...", 40)) / 2,screenHeight / 2 + 40,40, ORANGE);
            //Border
            DrawRectangleLinesEx((Rectangle) {screenWidth / 2 - 1000,screenHeight / 2 - 500, 2000, 850 },6, SKYBLUE);
            //Effects
            DrawCircleGradient(screenWidth/4, screenHeight/2 + 200, 100, PINK, RED);
            DrawCircleGradient(screenWidth/8, screenHeight/2 + 600, 350, YELLOW, ORANGE);
            DrawCircleGradient(screenWidth - 350, screenHeight - 1200, 200, MAGENTA, DARKPURPLE);
            DrawCircleGradient(screenWidth - 700, screenHeight - 200, 150, SKYBLUE, DARKBLUE);
        } else {
            DrawText("move dude with keys", 10, 10, 20, DARKGRAY);
            exampleGuy1.drawEntity();
            //DrawCircleV(ballPosition, 50, MAROON);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
