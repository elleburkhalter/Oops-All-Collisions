#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stack>

class StateMachine
{
public:
    void revert_state();
    template <typename T>
    void transition_state(const T& state);
    template <typename T>
    [[nodiscard]] T get_state() const;

private:
    std::stack<int> game_states{};
};

template <typename T>
T StateMachine::get_state() const
{
    return static_cast<T>(this->game_states.top());
}

template <typename T>
void StateMachine::transition_state(const T& state)
{
    this->game_states.push(static_cast<int>(state));
}

#endif //STATEMACHINE_H
