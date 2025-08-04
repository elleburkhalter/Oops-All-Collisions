
#ifndef RAYLIBRENDERER_H
#define RAYLIBRENDERER_H

#include <optional>
#include <raylib.h>
#include <renderer/ui_object/text/RaylibText.h>
#include <renderer/RendererInterface.h>
#include <event_loop/StateMachine.h>
#include <constants.h>

// This will implement RendererInterface interface to allow for visualization with
// Raylib.
class RaylibRenderer final : public RendererInterface
{
public:
    RaylibRenderer();
    ~RaylibRenderer() override;

    [[nodiscard]] static double get_screen_width() { return static_cast<double>(GetScreenWidth()); };
    [[nodiscard]] static double get_screen_height() { return static_cast<double>(GetScreenHeight()); };

    void draw_entity(const EntityInterface& entity) override;

    void draw_box(const OopsBoundingBox& bounding_box) override;
    void draw_point(Point point) override;
    void draw_circle(Ball ball) override;
    void draw_text(const TextInterface& text) override;

    void before_draw() override;
    void after_draw() override;

    void update_view_area();
    void zoom_view_area(double scroll_amount);
    void move_view_area(double x, double y);
    void unset_last_point();

    void draw_title_screen() const override;
private:
    static constexpr double ZOOM_SPEED = SCROLL_ZOOM_SPEED;

    OopsBoundingBox view_area;
    StateMachine game_state{};
    std::optional<Point> last_point = std::nullopt;
};
#endif //RAYLIBRENDERER_H
