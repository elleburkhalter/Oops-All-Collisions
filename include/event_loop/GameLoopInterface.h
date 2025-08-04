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

    virtual void update_collisions();
    virtual void update_entities(double dt);
    virtual void render();

    virtual void instantiate_entities(size_t count);
    virtual void run() = 0;

private:
    void render_game();
    void render_title_screen();

    MouseHandlerInterface& mouse_handler;
    ContainerInterface& container;
    RendererInterface& renderer;
    StateMachine state_machine;
};

#endif //GAMELOOPINTERFACE_H
