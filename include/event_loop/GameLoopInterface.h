#ifndef GAMELOOPINTERFACE_H
#define GAMELOOPINTERFACE_H

#include <event_loop/GameLoopInterface.h>
#include <event_loop/StateMachine.h>
#include <data_structures/ContainerInterface.h>
#include <event_loop/GameState.h>
#include <mouse_handler/MouseHandlerInterface.h>

class GameLoopInterface
{
public:
    virtual ~GameLoopInterface() = default;

    explicit GameLoopInterface(ContainerInterface& container, RendererInterface& renderer, MouseHandlerInterface& mouse_handler):
    container(container), renderer(renderer), mouse_handler(mouse_handler)
    {state_machine.transition_state<GameState>(GameState::TITLE_SCREEN_STATE);};

    [[nodiscard]] virtual bool is_running() = 0;
    [[nodiscard]] virtual double get_dt() = 0;
    [[nodiscard]] virtual GameState get_state() { return state_machine.get_state<GameState>(); }

    virtual void set_state(const GameState state) { state_machine.transition_state<GameState>(state); };
    virtual void revert_state() { state_machine.revert_state(); };

    virtual void initialize() = 0;
    virtual void update_collisions();
    virtual void update_entities(double dt);
    virtual void render();

    virtual void instantiate_entities(size_t count);
    virtual void run();

private:
    void render_game();
    void render_title_screen();

    MouseHandlerInterface& mouse_handler;
    ContainerInterface& container;
    RendererInterface& renderer;
    StateMachine state_machine;
};

#endif //GAMELOOPINTERFACE_H
