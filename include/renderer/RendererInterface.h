
#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

#include <spatial/OopsBoundingBox.h>
#include <game_object/interfaces/AgentInterface.h>
#include <game_object/interfaces/ProjectileInterface.h>
#include <raylib.h>
#include <ui_object/Text.h>

// This will be the abstract base class responsible for providing
// an interface for a visualization renderer (i.e. see the program
// with Raylib or use a NullRenderer to turn it off).

class RendererInterface
{
public:
    RendererInterface() = default;
    virtual ~RendererInterface() = default;

    // ----- Frame management -----
    //this stuff is not really needed IMO, mainly handled by raylib. 
    virtual bool is_open() const = 0;
    virtual void start_frame() = 0;
    virtual void finish_frame() = 0;

    // ----- Entities -----
    virtual void draw_agent(const AgentInterface& agent) = 0;
    virtual void draw_projectile(const ProjectileInterface& projectile) = 0;
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    virtual void draw_bounding_box(const BoundingBox& bounding_box) = 0;
    virtual void draw_text(const Text& text) = 0;
};

#endif //RENDERERINTERFACE_H
