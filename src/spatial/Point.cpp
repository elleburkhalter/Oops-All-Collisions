#include <cmath>
#include <spatial/Point.h>

double Point::get_distance_sq(const Point other) const
{
    const double x_diff = this->x - other.x;
    const double y_diff = this->y - other.y;
    return x_diff * x_diff + y_diff * y_diff;
}
double Point::get_distance_sq(const Point p1, const Point p2)
{
    const double x_diff = p1.x - p2.x;
    const double y_diff = p1.y - p2.y;
    return x_diff * x_diff + y_diff * y_diff;
}
double Point::get_distance(const Point other) const
{
    return std::sqrt(get_distance_sq(other));
}
double Point::get_distance(const Point p1, const Point p2)
{
    return std::sqrt(get_distance_sq(p1, p2));
}

Point Point::operator+(const Point other) const
{
    return {this->x + other.x, this->y + other.y};
}
Point Point::operator-(const Point other) const
{
    return {this->x - other.x, this->y - other.y};
}
Point Point::operator+=(const Point other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}
Point Point::operator-=(const Point other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
Point Point::operator*(const double scalar) const
{
    return {this->x * scalar, this->y * scalar};
}
Point Point::operator/(const double scalar) const
{
    return {this->x / scalar, this->y / scalar};
}
Point Point::operator*=(const double scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}
Point Point::operator/=(const double scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}
Point operator*(const double scalar, const Point other)
{
    return other * scalar;
}
bool Point::operator==(const Point other) const
{
    return this->x == other.x && this->y == other.y;
}
bool Point::operator!=(const Point other) const
{
    return !(*this == other);
}