#ifndef MOUSEHANDLERINTERFACE_H
#define MOUSEHANDLERINTERFACE_H

#include <list>
#include <functional>
#include <spatial/Point.h>
#include <mouse_handler/RaylibMouseFlags.h>

class MouseHandlerInterface
{
public:
    virtual ~MouseHandlerInterface() = default;

    [[nodiscard]] virtual bool is_left_down() = 0;
    [[nodiscard]] virtual bool is_middle_down() = 0;
    [[nodiscard]] virtual bool is_right_down() = 0;

    [[nodiscard]] virtual Point get_mouse_location() = 0;
    [[nodiscard]] virtual double get_mouse_scroll() = 0;

    virtual void handle_left_mouse();
    virtual void handle_middle_mouse();
    virtual void handle_right_mouse();

    virtual void handle_mouse();

    virtual void on_left(const double x, const double y) { for (const auto callback : on_left_) callback(x, y); }
    virtual void on_middle(const double x, const double y) { for (const auto callback : on_middle_) callback(x, y); }
    virtual void on_right(const double x, const double y) { for (const auto callback : on_right_) callback(x, y); }

    virtual void on_scroll(const double dy) { for (const auto callback : on_scroll_) callback(dy); }
    virtual void on_move(const double x, const double y) { for (const auto callback : on_move_) callback(x, y); }

    virtual void off_left(const double x, const double y) { for (const auto callback : off_left_) callback(x, y); }
    virtual void off_middle(const double x, const double y) { for (const auto callback : off_middle_) callback(x, y); }
    virtual void off_right(const double x, const double y) { for (const auto callback : off_right_) callback(x, y); }

    virtual void while_left(const double x, const double y) { for (const auto callback : while_left_) callback(x, y); }
    virtual void while_middle(const double x, const double y) { for (const auto callback : while_middle_) callback(x, y); }
    virtual void while_right(const double x, const double y) { for (const auto callback : while_right_) callback(x, y); }

    virtual void add_on_left(const std::function<void(double, double)> callback) { on_left_.push_back(callback); };
    virtual void add_on_middle(const std::function<void(double, double)> callback) { on_middle_.push_back(callback); };
    virtual void add_on_right(const std::function<void(double, double)> callback) { on_right_.push_back(callback); };

    virtual void add_on_scroll(const std::function<void(double)> callback) { on_scroll_.push_back(callback); };

    virtual void add_off_left(const std::function<void(double, double)> callback) { off_left_.push_back(callback); };
    virtual void add_off_middle(const std::function<void(double, double)> callback) { off_middle_.push_back(callback); };
    virtual void add_off_right(const std::function<void(double, double)> callback) { off_right_.push_back(callback); };

    virtual void add_while_left(const std::function<void(double, double)> callback) { while_left_.push_back(callback); };
    virtual void add_while_middle(const std::function<void(double, double)> callback) { while_middle_.push_back(callback); };
    virtual void add_while_right(const std::function<void(double, double)> callback) { while_right_.push_back(callback); };

private:
    [[nodiscard]] virtual bool is_left_flag_set() { return mouse_flags_ & MouseDownFlags::LEFT; }
    [[nodiscard]] virtual bool is_middle_flag_set() { return mouse_flags_ & MouseDownFlags::MIDDLE; }
    [[nodiscard]] virtual bool is_right_flag_set() { return mouse_flags_ & MouseDownFlags::RIGHT; }

    virtual void set_left_flag() { mouse_flags_ |= MouseDownFlags::LEFT; }
    virtual void unset_left_flag() { mouse_flags_ &= ~MouseDownFlags::LEFT; }
    virtual void set_left_flag(const bool active) { active ? set_left_flag() : unset_left_flag(); }

    virtual void set_middle_flag() { mouse_flags_ |= MouseDownFlags::MIDDLE; }
    virtual void unset_middle_flag() { mouse_flags_ &= ~MouseDownFlags::MIDDLE; }
    virtual void set_middle_flag(const bool active) { active ? set_middle_flag() : unset_middle_flag(); }

    virtual void set_right_flag() { mouse_flags_ |= MouseDownFlags::RIGHT; }
    virtual void unset_right_flag() { mouse_flags_ &= ~MouseDownFlags::RIGHT; }
    virtual void set_right_flag(const bool active) { active ? set_right_flag() : unset_right_flag(); }

    uint8_t mouse_flags_ = 0;
    Point last_location{};

    std::list<std::function<void(double, double)>> on_left_{};
    std::list<std::function<void(double, double)>> on_right_{};
    std::list<std::function<void(double, double)>> on_middle_{};

    std::list<std::function<void(double)>> on_scroll_{};
    std::list<std::function<void(double, double)>> on_move_{};

    std::list<std::function<void(double, double)>> off_left_{};
    std::list<std::function<void(double, double)>> off_right_{};
    std::list<std::function<void(double, double)>> off_middle_{};

    std::list<std::function<void(double, double)>> while_left_{};
    std::list<std::function<void(double, double)>> while_right_{};
    std::list<std::function<void(double, double)>> while_middle_{};
};

#endif //MOUSEHANDLERINTERFACE_H
