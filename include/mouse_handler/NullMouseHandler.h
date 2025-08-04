#ifndef NULLMOUSEHANDLER_H
#define NULLMOUSEHANDLER_H
#include <mouse_handler/MouseHandlerInterface.h>

class NullMouseHandler final : public MouseHandlerInterface
{
public:
    void handle_click() override {};
};


#endif //NULLMOUSEHANDLER_H
