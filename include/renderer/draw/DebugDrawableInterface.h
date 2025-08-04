#ifndef DEBUGDRAWABLEINTERFACE_H
#define DEBUGDRAWABLEINTERFACE_H

#include <renderer/RendererInterface.h>

class RendererInterface;

class DebugDrawableInterface
{
public:
    virtual ~DebugDrawableInterface() = default;
    virtual void draw_debug(RendererInterface& renderer) const = 0;
};

#endif //DEBUGDRAWABLEINTERFACE_H
