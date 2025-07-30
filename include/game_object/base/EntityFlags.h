#ifndef ENTITYFLAGS_H
#define ENTITYFLAGS_H

#include <cinttypes>

enum EntityFlags : uint8_t
{
    MovementEnabled  = 1,
    CollisionEnabled = 1 << 1
};

#endif //ENTITYFLAGS_H
