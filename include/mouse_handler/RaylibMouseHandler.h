#ifndef RAYLIBMOUSEHANDLER_H
#define RAYLIBMOUSEHANDLER_H
#include <mouse_handler/MouseHandlerInterface.h>

class RaylibMouseHandler final : public MouseHandlerInterface
{
    bool is_right_down() override;
    bool is_left_down() override;
    bool is_middle_down() override;

    Point get_mouse_location() override;
    double get_mouse_scroll() override;
};

#endif //RAYLIBMOUSEHANDLER_H
