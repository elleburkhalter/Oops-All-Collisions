#ifndef POINT_H
#define POINT_H

struct Point
{
    Point(): x(0.0), y(0.0) {};
    Point(const double x, const double y): x(x), y(y) {};

    static inline double get_distance_sq(Point p1, Point p2);
    static inline double get_distance(Point p1, Point p2);
    [[nodiscard]] inline double get_distance_sq(Point other) const;  // Intentionally not by reference; small struct :)
    [[nodiscard]] inline double get_distance(Point other) const;

    inline Point operator+(Point other) const;
    inline Point operator-(Point other) const;
    inline Point operator+=(Point other);
    inline Point operator-=(Point other);

    double x;
    double y;
};

#endif //POINT_H
