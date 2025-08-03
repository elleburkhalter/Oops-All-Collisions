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

#endif //STATEMACHINE_H
