#include <random/NormalDistribution.h>
#include <event_loop/GameLoop.h>
#include <game_object/enemies/BasicEnemy.h>
#include <event_loop/GameState.h>

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
    renderer.draw_title_screen();
}


void GameLoop::render()
{
    if (state_machine.get_state<GameState>() == GameState::TITLE_SCREEN_STATE)
    {
        this->render_title_screen();
    }
    else if (state_machine.get_state<GameState>() == GameState::ACTIVE_GAME_STATE)
    {
        this->render_game();
    }
}
