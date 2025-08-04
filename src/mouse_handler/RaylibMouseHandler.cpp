#include <raylib.h>
#include <mouse_handler/RaylibMouseHandler.h>

void RaylibMouseHandler::handle_click()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) this->handle_left_click(GetMouseX(), GetMouseY());
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) this->handle_right_click(GetMouseX(), GetMouseY());
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) this->handle_middle_click(GetMouseX(), GetMouseY());

    if (Is)
}

