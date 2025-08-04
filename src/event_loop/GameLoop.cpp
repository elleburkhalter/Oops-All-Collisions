#include <raylib.h>
#include <random/NormalDistribution.h>
#include <event_loop/GameLoop.h>
#include <game_object/enemies/BasicEnemy.h>
#include <renderer/ui_object/text/RaylibText.h>

void GameLoop::instantiate_entities(const size_t count)
{
    for (size_t i = 0; i < count; i++) container.add_basic_enemy();
}

void GameLoop::update_collisions()
{
    for (const auto& [fst, snd] : container.get_all_collisions())
    {
        auto success = fst->get_collider().resolve_collision_with(snd->get_collider());
    }
}

void GameLoop::update_entities(const double dt)
{
    for (const auto entity : container.get_all_entities())
    {
        entity->update(dt);
    }
}

void GameLoop::render_game()
{
    container.draw_debug(renderer);
    for (const auto entity : container.get_all_entities())
    {
        renderer.draw_entity(entity);
    }
}

void GameLoop::render_title_screen()
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


void GameLoop::render() const
{

}
