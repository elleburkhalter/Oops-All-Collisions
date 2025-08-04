#include <raylib.h>
#include <mouse_handler/RaylibMouseHandler.h>

Point RaylibMouseHandler::get_mouse_location()
{
    const double x = GetMouseX();
    const double y = GetMouseY();
    return {x, y};
}
double RaylibMouseHandler::get_mouse_scroll()
{
    return static_cast<double>(GetMouseWheelMove());
}
bool RaylibMouseHandler::is_left_down()
{
    return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}
bool RaylibMouseHandler::is_middle_down()
{
    return IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
}
bool RaylibMouseHandler::is_right_down()
{
    return IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
}

