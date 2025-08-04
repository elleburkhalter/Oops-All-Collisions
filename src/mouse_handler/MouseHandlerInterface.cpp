#include <mouse_handler/MouseHandlerInterface.h>

void MouseHandlerInterface::handle_left_mouse()
{
    if (is_left_down() && !is_left_flag_set())  // LMB just pressed
    {
        const Point loc = get_mouse_location();
        on_left(loc.x, loc.y);
        set_left_flag(true);
        return;
    }
    if (is_left_down())  // LMB is being held down
    {
        const Point loc = get_mouse_location();
        while_left(loc.x, loc.y);
        return;
    }
    if (is_left_flag_set())  // LMB just released
    {
        const Point loc = get_mouse_location();
        off_left(loc.x, loc.y);
        set_left_flag(false);
        return;
    }
}

void MouseHandlerInterface::handle_middle_mouse()
{
    if (is_middle_down() && !is_middle_flag_set())  // MMB just pressed
    {
        const Point loc = get_mouse_location();
        on_middle(loc.x, loc.y);
        set_middle_flag(true);
        return;
    }
    if (is_middle_down())  // MMB is being held down
    {
        const Point loc = get_mouse_location();
        while_middle(loc.x, loc.y);
        return;
    }
    if (is_middle_flag_set())  // MMB just released
    {
        const Point loc = get_mouse_location();
        off_middle(loc.x, loc.y);
        set_middle_flag(false);
        return;
    }
}

void MouseHandlerInterface::handle_right_mouse()
{
    if (is_right_down() && !is_right_flag_set())  // RMB just pressed
    {
        const Point loc = get_mouse_location();
        on_right(loc.x, loc.y);
        set_right_flag(true);
        return;
    }
    if (is_right_down())  // RMB is being held down
    {
        const Point loc = get_mouse_location();
        while_right(loc.x, loc.y);
        return;
    }
    if (is_right_flag_set())  // RMB just released
    {
        const Point loc = get_mouse_location();
        off_right(loc.x, loc.y);
        set_right_flag(false);
        return;
    }
}

void MouseHandlerInterface::handle_mouse()
{
    if (const Point current_location = get_mouse_location(); current_location.x != last_location.x || current_location.y != last_location.y)
    {
        on_move(current_location.x, current_location.y);
        last_location = current_location;
    }
    if (const double scroll = get_mouse_scroll(); scroll != 0.0)
    {
        on_scroll(scroll);
    }
    handle_left_mouse();
    handle_middle_mouse();
    handle_right_mouse();
}
