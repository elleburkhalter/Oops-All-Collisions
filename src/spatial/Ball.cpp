#include <spatial/Ball.h>

Point Ball::get_centroid() const
{
    return this->center;
}
bool Ball::contains(const Point p) const
{
    return Point::get_distance_sq(this->center, p) < this->radius * this->radius;
}

