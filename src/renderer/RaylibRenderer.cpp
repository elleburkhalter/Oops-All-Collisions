#include <renderer/RaylibRenderer.h>
#include <raylib.h>

RaylibRenderer::RaylibRenderer()
{
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    const int monitor = GetCurrentMonitor();

    const int screen_width = GetMonitorHeight(monitor);
    const int screen_height = GetMonitorWidth(monitor);

    InitWindow(screen_width, screen_height, "Collision Project");
    SetTargetFPS(60);
}


RaylibRenderer::~RaylibRenderer()
{
    CloseWindow();
}

void RaylibRenderer::render_title_screen()
{
    DrawText("Oops! All Collisions",(screenWidth - MeasureText("Oops! All Collisions", 120)) / 2,screenHeight / 2 - 250,120, BLUE);
    DrawText("Created by Logan Dapp, Derrick Davison, and Elle Burkhalter",(screenWidth - MeasureText("Created by Logan Dapp, Derrick Davison, and Elle Burkhalter", 50)) / 2,screenHeight / 2 - 120, 50, GREEN);
    DrawText("Click anywhere to begin...",(screenWidth - MeasureText("Click anywhere to begin...", 40)) / 2,screenHeight / 2 + 40,40, ORANGE);
    //Border
    //DrawRectangleLinesEx((Rectangle) {screenWidth / 2 - 1000,screenHeight / 2 - 500, 2000, 850 },6, SKYBLUE);
    //Effects
    DrawCircleGradient(screenWidth/4, screenHeight/2 + 200, 100, PINK, RED);
    DrawCircleGradient(screenWidth/8, screenHeight/2 + 600, 350, YELLOW, ORANGE);
    DrawCircleGradient(screenWidth - 350, screenHeight - 1200, 200, MAGENTA, DARKPURPLE);
    DrawCircleGradient(screenWidth - 700, screenHeight - 200, 150, SKYBLUE, DARKBLUE);
}

