#include <renderer/RaylibRenderer.h>
#include <raylib.h>
#include <renderer/ui_object/text/RaylibText.h>

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
    RaylibText title_text{"Oop! All Collisions", 120, {0, -250}};
    title_text.set_alignment(TextAlignment::UC);
    title_text.set_anchor(TextLocation::MC_RELATIVE);
    title_text.draw(BLUE);

    RaylibText author_text{"Created by Logan Dapp, Derrick Davison, and Elle Burkhalter", 40, {0, -120}};
    author_text.set_alignment(TextAlignment::UC);
    author_text.set_anchor(TextLocation::MC_RELATIVE);
    author_text.draw(ORANGE);

    RaylibText continue_text{"Click anywhere to begin...", 40, {0, 40}};
    continue_text.set_alignment(TextAlignment::UC);
    continue_text.set_anchor(TextLocation::MC_RELATIVE);
    continue_text.draw(ORANGE);

    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    DrawCircleGradient(screen_width/4, screen_height/2 + 200, 100, PINK, RED);
    DrawCircleGradient(screen_width/8, screen_height/2 + 600, 350, YELLOW, ORANGE);
    DrawCircleGradient(screen_width - 350, screen_height - 1200, 200, MAGENTA, DARKPURPLE);
    DrawCircleGradient(screen_width - 700, screen_height - 200, 150, SKYBLUE, DARKBLUE);
}

