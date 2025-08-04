#ifndef RAYLIBGAMELOOP_H
#define RAYLIBGAMELOOP_H

#include <event_loop/GameLoopInterface.h>
#include <renderer/RaylibRenderer.h>
#include <mouse_handler/RaylibMouseHandler.h>

class RaylibGameLoop final : public GameLoopInterface
{
public:
    RaylibGameLoop(ContainerInterface& container, RaylibRenderer& renderer, RaylibMouseHandler& mouse_handler):
    GameLoopInterface(container, renderer, mouse_handler)
    {};

    void run() override;
private:

};

#endif //RAYLIBGAMELOOP_H
