
#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

#include <spatial/OopsBoundingBox.h>
#include <spatial/Ball.h>
#include <game_object/interfaces/AgentInterface.h>
#include <game_object/interfaces/ProjectileInterface.h>
#include <renderer/ui_object/text/TextInterface.h>

// This will be the abstract base class responsible for providing
// an interface for a visualization renderer (i.e. see the program
// with Raylib or use a NullRenderer to turn it off).

struct OopsBoundingBox;

class RendererInterface
{
public:
    RendererInterface() = default;
    virtual ~RendererInterface() = default;

    // ----- Pre-draw and Post-draw hooks -----
    virtual void before_draw() = 0;
    virtual void after_draw() = 0;

    // ----- Entities -----
    virtual void draw_entity(const EntityInterface& entity) = 0;

    // ----- Debug visualization -----
    virtual void draw_box(const OopsBoundingBox& bounding_box) = 0;
    virtual void draw_point(Point point) = 0;
    virtual void draw_circle(Ball ball) = 0;
    virtual void draw_text(const TextInterface& text) = 0;

    virtual void draw_title_screen() const = 0;
};

#endif //RENDERERINTERFACE_H
