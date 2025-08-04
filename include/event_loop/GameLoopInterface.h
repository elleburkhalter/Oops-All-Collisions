#ifndef GAMELOOPINTERFACE_H
#define GAMELOOPINTERFACE_H

#include <data_structures/ContainerInterface.h>

class GameLoopInterface
{
public:
    virtual ~GameLoopInterface() = default;

    virtual void update_collisions() = 0;
    virtual void update_entities(double dt) = 0;
    virtual void render() = 0;
    virtual void instantiate_entities(size_t count) = 0;

    virtual void run() = 0;
};

#endif //GAMELOOPINTERFACE_H
