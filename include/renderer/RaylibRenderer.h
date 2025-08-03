
#ifndef RAYLIBRENDERER_H
#define RAYLIBRENDERER_H

#include <raylib.h>
#include <renderer/RendererInterface.h>

// This will implement RendererInterface interface to allow for visualization with
// Raylib.
class RaylibRenderer final : public RendererInterface
{
    void draw_agent(const AgentInterface& agent) override;
    void draw_projectile(const ProjectileInterface& projectile) override;

    void draw_box(const OopsBoundingBox& bounding_box) override;
    void draw_point(Point point) override;
    void draw_circle(Ball ball) override;
    void draw_text(const Text& text) override;

};
#endif //RAYLIBRENDERER_H
