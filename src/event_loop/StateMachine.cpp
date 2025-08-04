#include <event_loop/StateMachine.h>

void StateMachine::revert_state()
{
    this->game_states.pop();
}
