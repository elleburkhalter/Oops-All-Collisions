#ifndef RAYLIBGAMELOOP_H
#define RAYLIBGAMELOOP_H

#include <raylib.h>
#include <event_loop/GameLoopInterface.h>
#include <event_loop/StateMachine.h>
#include <data_structures/ContainerInterface.h>

class GameLoop final : public GameLoopInterface
{
public:
    explicit GameLoop(ContainerInterface& container, RendererInterface& renderer):
    container(container), renderer(renderer)
    {};

    void update_collisions() override;
    void update_entities(double dt) override;
    void render() const override;

    void instantiate_entities(size_t count) override;
    void run() override;

private:
    void render_game();
    void render_title_screen();

    ContainerInterface& container;
    RendererInterface& renderer;
    StateMachine state_machine;
};

#endif //RAYLIBGAMELOOP_H
