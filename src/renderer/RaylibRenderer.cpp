#include <renderer/RaylibRenderer.h>
#include <raylib.h>
#include <cmath>
#include <renderer/ui_object/text/RaylibText.h>

RaylibRenderer::RaylibRenderer()
{
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    const int monitor = GetCurrentMonitor();

    const int screen_width = GetMonitorHeight(monitor);
    const int screen_height = GetMonitorWidth(monitor);

    view_area = OopsBoundingBox{-static_cast<double>(screen_width) / 2, -static_cast<double>(screen_height) / 2, static_cast<double>(screen_width) / 2, static_cast<double>(screen_height) / 2};

    InitWindow(screen_width, screen_height, "Collision Project");
    SetTargetFPS(60);
}


RaylibRenderer::~RaylibRenderer()
{
    CloseWindow();
}

void RaylibRenderer::update_view_area()
{
    const double screen_aspect_ratio = get_screen_height() / get_screen_width();

    if (const double view_area_aspect_ratio = view_area.get_height() / view_area.get_width(); screen_aspect_ratio != view_area_aspect_ratio)
    {
        // Window changed size, so update view_area height accordingly.
        const double target_height = view_area.get_width() * screen_aspect_ratio;
        const double current_height = view_area.get_height();
        const double y_offset = 0.5 * (target_height - current_height);

        view_area.min.y -= y_offset;
        view_area.max.y += y_offset;
    }
}

void RaylibRenderer::unset_last_point()
{
    last_point = std::nullopt;
}

void RaylibRenderer::move_view_area(double x, double y)
{
    update_view_area();

    if (last_point == std::nullopt)
    {
        last_point = {x, y};
        return;
    }

    const double view_area_conversion = view_area.get_width() / get_screen_width();

    const double dx = (x - last_point->x) * view_area_conversion;
    const double dy = (y - last_point->y) * view_area_conversion;

    view_area = {view_area.min.x + dx, view_area.min.y + dy, view_area.max.x + dx, view_area.max.y + dy};
}


void RaylibRenderer::zoom_view_area(const double scroll_amount)
{
    update_view_area();

    const double multiplier = std::exp(-scroll_amount * ZOOM_SPEED);
    const Point center = view_area.get_centroid();
    const double width = view_area.get_width();
    const double height = view_area.get_height();

    view_area = OopsBoundingBox{center.x - width * multiplier * 0.5, center.y - height * multiplier * 0.5, center.x + width * multiplier * 0.5, center.y + height * multiplier * 0.5};
}


void RaylibRenderer::draw_box(const OopsBoundingBox& bounding_box)
{
    const auto screen_width = get_screen_height();
    const auto screen_height = get_screen_width();

    const Point draw_scale = {screen_width * bounding_box.get_width() / view_area.get_width(), screen_height * bounding_box.get_height() / view_area.get_height()};
    const Point top_coord = screen_width * (bounding_box.min - view_area.min) / view_area.get_width();
    const Point bottom_coord = top_coord + draw_scale;

    DrawRectangleLines(static_cast<int>(top_coord.x), static_cast<int>(top_coord.y), static_cast<int>(bottom_coord.x), static_cast<int>(bottom_coord.y), GREEN);
}

void RaylibRenderer::draw_point(const Point point)
{
    const Point to_draw = get_screen_width() * (point - view_area.min) / view_area.get_width();;
    DrawCircle(static_cast<int>(to_draw.x), static_cast<int>(to_draw.y), 1.0, RED);
}

void RaylibRenderer::draw_circle(const Ball ball)
{
    const double world_scale = get_screen_width() / view_area.get_width();
    const Point center = (ball.center - view_area.min) * world_scale;
    const double radius = ball.radius * world_scale;

    DrawCircleLines(static_cast<int>(center.x), static_cast<int>(center.y), static_cast<float>(radius), YELLOW);
}

void RaylibRenderer::draw_text(const TextInterface& text)
{
    text.draw();
}

void RaylibRenderer::draw_entity(const EntityInterface& entity)
{
    entity.draw(*this);
}
void RaylibRenderer::draw_title_screen() const
{
    RaylibText title_text{"Oop! All Collisions", 120, {0, -250}};
    title_text.set_alignment(TextAlignment::UC);
    title_text.set_anchor(TextLocation::MC_RELATIVE);
    title_text.draw(BLUE);

    RaylibText author_text{"Created by Logan Dapp, Derrick Davison, and Elle Burkhalter", 40, {0, -120}};
    author_text.set_alignment(TextAlignment::UC);
    author_text.set_anchor(TextLocation::MC_RELATIVE);
    author_text.draw(ORANGE);

    RaylibText continue_text{"Click anywhere to begin...", 40, {0, 40}};
    continue_text.set_alignment(TextAlignment::UC);
    continue_text.set_anchor(TextLocation::MC_RELATIVE);
    continue_text.draw(ORANGE);

    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    DrawCircleGradient(screen_width/4, screen_height/2 + 200, 100, PINK, RED);
    DrawCircleGradient(screen_width/8, screen_height/2 + 600, 350, YELLOW, ORANGE);
    DrawCircleGradient(screen_width - 350, screen_height - 1200, 200, MAGENTA, DARKPURPLE);
    DrawCircleGradient(screen_width - 700, screen_height - 200, 150, SKYBLUE, DARKBLUE);
}

