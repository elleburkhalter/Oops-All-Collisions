//
// Created by logan on 7/29/2025.
//
#include <renderer/RendererInterface.h>
#include <unordered_map>

//Mapping from collision count to color
std::unordered_map<int, Color> collisionColorMap = {
    {0, DARKBLUE},
    {1, BLUE},
    {2, GREEN},
    {3, YELLOW},
    {4, ORANGE},
    {5, RED},
    {6, PINK},
    {7, MAGENTA},
};

// Function to retrieve color based on collision count
Color getBallColor(int collisionCount) {
    if (collisionColorMap.find(collisionCount) != collisionColorMap.end()) {
        return collisionColorMap[collisionCount];
    }
    return PURPLE; // Default color
}
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
            //inputs and logic during game loop go here
            //instantiate entities here
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
            //drawing during game loop goes here
            
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
