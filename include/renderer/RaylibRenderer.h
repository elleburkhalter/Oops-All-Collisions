
#ifndef RAYLIBRENDERER_H
#define RAYLIBRENDERER_H

#include <raylib.h>

// This will implement RendererInterface interface to allow for visualization with
// Raylib.
class RaylibRenderer
{
    public:
    virtual int start();
};
#endif //RAYLIBRENDERER_H
