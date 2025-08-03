
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

    // ----- Entities -----
    virtual void draw_agent(const AgentInterface& agent) = 0;
    virtual void draw_projectile(const ProjectileInterface& projectile) = 0;
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    virtual void draw_box(const OopsBoundingBox& bounding_box) = 0;
    virtual void draw_point(Point point) = 0;
    virtual void draw_circle(Ball ball) = 0;
    virtual void draw_text(const TextInterface& text) = 0;
};

#endif //RENDERERINTERFACE_H
