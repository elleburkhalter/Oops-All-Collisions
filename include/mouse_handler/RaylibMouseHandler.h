#ifndef RAYLIBMOUSEHANDLER_H
#define RAYLIBMOUSEHANDLER_H
#include <mouse_handler/MouseHandlerInterface.h>

class RaylibMouseHandler final : public MouseHandlerInterface
{
    void handle_click() override;
};

#endif //RAYLIBMOUSEHANDLER_H
