#ifndef RAYLIBGAMELOOP_H
#define RAYLIBGAMELOOP_H

#include <raylib.h>
#include <event_loop/GameLoopInterface.h>
#include <data_structures/ContainerInterface.h>

class GameLoop final : public GameLoopInterface
{
public:
    explicit GameLoop(ContainerInterface& container, RendererInterface& renderer):
    container(container), renderer(renderer)
    {};

    double update_collisions() const override;
    double update_entities() const override;
    double render() const override;

    void instantiate_entities(size_t count) override;
    void run() override;

private:
    ContainerInterface& container;
    RendererInterface& renderer;
};

#endif //RAYLIBGAMELOOP_H
