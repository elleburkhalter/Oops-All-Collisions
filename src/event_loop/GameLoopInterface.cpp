#include <random/NormalDistribution.h>
#include <event_loop/GameLoopInterface.h>
#include <game_object/enemies/BasicEnemy.h>
#include <event_loop/GameState.h>

void GameLoopInterface::instantiate_entities(const size_t count)
{
    for (size_t i = 0; i < count; i++) container.add_basic_enemy();
}

void GameLoopInterface::update_collisions()
{
    for (const auto& [fst, snd] : container.get_all_collisions())
    {
        auto success = fst->get_collider().resolve_collision_with(snd->get_collider());
    }
}

void GameLoopInterface::update_entities(const double dt)
{
    for (const auto entity : container.get_all_entities())
    {
        entity->update(dt);
    }
}

void GameLoopInterface::render_game()
{
    container.draw_debug(renderer);
    for (const auto entity : container.get_all_entities())
    {
        renderer.draw_entity(*entity);
    }
}

void GameLoopInterface::render_title_screen()
{
    renderer.draw_title_screen();
}

void GameLoopInterface::render()
{
    this->renderer.before_draw();
    if (state_machine.get_state<GameState>() == GameState::TITLE_SCREEN_STATE)
    {
        this->render_title_screen();
    }
    else if (state_machine.get_state<GameState>() == GameState::ACTIVE_GAME_STATE)
    {
        this->render_game();
    }
    this->renderer.after_draw();
}

void GameLoopInterface::run()
{
    while (is_running())
    {
        if (get_state() == GameState::ACTIVE_GAME_STATE)
        {
            this->update_collisions();
            const double dt = get_dt();
            this->update_entities(dt);
            this->container.draw_debug(this->renderer);
        }
        this->update_hook();
        this->render();
    }
}

