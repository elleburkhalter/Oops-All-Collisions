#ifndef RAYLIBGAMELOOP_H
#define RAYLIBGAMELOOP_H

#include <event_loop/GameLoopInterface.h>
#include <renderer/RaylibRenderer.h>
#include <mouse_handler/RaylibMouseHandler.h>
#include <constants.h>

class RaylibGameLoop final : public GameLoopInterface
{
public:
    RaylibGameLoop(ContainerInterface& container, RaylibRenderer& renderer, RaylibMouseHandler& mouse_handler):
    GameLoopInterface(container, renderer, mouse_handler), renderer(renderer), mouse_handler(mouse_handler)
    {};

    void update_hook() override;
    bool is_running() override;
    double get_dt() override;
    void initialize() override;

private:

    RaylibRenderer& renderer;
    RaylibMouseHandler& mouse_handler;
    static constexpr size_t NUM_ENTITIES = N_ENTITIES;

};

#endif //RAYLIBGAMELOOP_H
