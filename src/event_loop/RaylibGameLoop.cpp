#include <event_loop/RaylibGameLoop.h>

bool RaylibGameLoop::is_running()
{
    return !WindowShouldClose();
}
double RaylibGameLoop::get_dt()
{
    return GetFrameTime();
}
void RaylibGameLoop::initialize()
{
    this->instantiate_entities(NUM_ENTITIES);

    this->mouse_handler.add_while_left([&](const double x, const double y) -> void { this->renderer.move_view_area(x, y); });
    this->mouse_handler.add_off_left([&](const double _, const double __) -> void { this->renderer.unset_last_point(); });
    this->mouse_handler.add_on_scroll([&](const double dy) -> void { this->renderer.zoom_view_area(dy); });
}
void RaylibGameLoop::update_hook()
{
    this->renderer.update_view_area();
    this->mouse_handler.handle_mouse();
}


