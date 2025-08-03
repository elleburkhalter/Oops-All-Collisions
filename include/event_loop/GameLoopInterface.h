#ifndef GAMELOOPINTERFACE_H
#define GAMELOOPINTERFACE_H

#include <data_structures/ContainerInterface.h>

class GameLoopInterface
{
public:
    virtual ~GameLoopInterface() = default;

    virtual double update_collisions() const = 0;
    virtual double update_entities() const = 0;
    virtual double render() const = 0;
    virtual void instantiate_entities(size_t count) = 0;

    virtual void run() = 0;
};

#endif //GAMELOOPINTERFACE_H
