#include <event_loop/StateMachine.h>

template <typename T>
T StateMachine::get_state() const
{
    return static_cast<T>(this->game_states.top());
}

void StateMachine::revert_state()
{
    this->game_states.pop();
}

template <typename T>
void StateMachine::transition_state(const T& state)
{
    this->game_states.push(static_cast<int>(state));
}
