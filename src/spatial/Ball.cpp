#include <spatial/Ball.h>

inline bool Ball::contains(const Point p) const
{
    return Point::get_distance_sq(this->center, p) < this->radius * this->radius;
}

