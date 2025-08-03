
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
public:
    RaylibRenderer();
    ~RaylibRenderer() override;

    [[nodiscard]] static double get_screen_width() { return static_cast<double>(GetScreenWidth()); };
    [[nodiscard]] static double get_screen_height() { return static_cast<double>(GetScreenHeight()); };

    void draw_agent(const AgentInterface& agent) override;
    void draw_projectile(const ProjectileInterface& projectile) override;

    void draw_box(const OopsBoundingBox& bounding_box) override;
    void draw_point(Point point) override;
    void draw_circle(Ball ball) override;
    void draw_text(const RaylibText& text) override;

    void update_view_area();

private:

    static void render_title_screen();
    void render_game_screen();

    OopsBoundingBox view_area;
    StateMachine game_state{};

};
#endif //RAYLIBRENDERER_H
