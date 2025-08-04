#ifndef RAYLIBMOUSEFLAGS_H
#define RAYLIBMOUSEFLAGS_H

#include <cinttypes>

enum MouseDownFlags : uint8_t
{
    LEFT = 1 << 0,
    MIDDLE = 1 << 1,
    RIGHT = 1 << 2
};

#endif //RAYLIBMOUSEFLAGS_H
