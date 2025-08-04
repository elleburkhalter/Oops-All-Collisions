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
    // TODO: add mouse callbacks.
}


