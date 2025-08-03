
#ifndef RAYLIBRENDERER_H
#define RAYLIBRENDERER_H

#include <raylib.h>
#include <renderer/ui_object/text/RaylibText.h>
#include <renderer/RendererInterface.h>
#include <event_loop/StateMachine.h>

// This will implement RendererInterface interface to allow for visualization with
// Raylib.
class RaylibRenderer final : public RendererInterface
{
    RaylibRenderer();
    ~RaylibRenderer() override;

    void draw_agent(const AgentInterface& agent) override;
    void draw_projectile(const ProjectileInterface& projectile) override;

    void draw_box(const OopsBoundingBox& bounding_box) override;
    void draw_point(Point point) override;
    void draw_circle(Ball ball) override;
    void draw_text(const RaylibText& text) override;

private:
    static void render_title_screen();
    void render_game_screen();

    StateMachine game_state{};

};
#endif //RAYLIBRENDERER_H
