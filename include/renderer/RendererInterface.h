
#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

#include <spatial/BoundingBox.h>
#include <game_object/base/AgentABC.h>
#include <game_object/base/ProjectileABC.h>
#include <ui_object/Text.h>

// This will be the abstract base class responsible for providing
// an interface for a visualization renderer (i.e. see the program
// with SFML or use a NullRenderer to turn it off).

class RendererInterface
{
    virtual ~RendererInterface() = default;

    // ----- Frame management -----
    virtual bool is_open() const = 0;
    virtual void start_frame() = 0;
    virtual void finish_frame() = 0;

    // ----- Entities -----
    virtual void draw_agent(const AgentABC& agent) = 0;
    virtual void draw_projectile(const ProjectileABC& projectile) = 0;
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    virtual void draw_bounding_box(const BoundingBox& bounding_box) = 0;
    virtual void draw_text(const Text& text) = 0;
};

#endif //RENDERERINTERFACE_H
