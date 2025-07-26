#include <cmath>
#include <spatial/Point.h>

inline double Point::get_distance_sq(const Point other) const
{
    const double x_diff = this->x - other.x;
    const double y_diff = this->y - other.y;
    return x_diff * x_diff + y_diff * y_diff;
}
inline double Point::get_distance_sq(Point p1, Point p2)
{
    const double x_diff = p1.x - p2.x;
    const double y_diff = p1.y - p2.y;
    return x_diff * x_diff + y_diff * y_diff;
}
inline double Point::get_distance(const Point other) const
{
    return std::sqrt(get_distance_sq(other));
}
inline double Point::get_distance(Point p1, Point p2)
{
    return std::sqrt(get_distance_sq(p1, p2));
}

