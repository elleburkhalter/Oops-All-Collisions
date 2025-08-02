#ifndef POINT_H
#define POINT_H

struct Point
{
    Point(): x(0.0), y(0.0) {};
    Point(const double x, const double y): x(x), y(y) {};

    static double get_distance_sq(Point p1, Point p2);
    static double get_distance(Point p1, Point p2);
    [[nodiscard]] double get_distance_sq(Point other) const;  // Intentionally not by reference; small struct :)
    [[nodiscard]] double get_distance(Point other) const;

    Point operator+(Point other) const;
    Point operator-(Point other) const;
    Point operator+=(Point other);
    Point operator-=(Point other);
    Point operator*(double scalar) const;
    Point operator/(double scalar) const;
    Point operator*=(double scalar);
    Point operator/=(double scalar);
    bool operator==(Point other) const;
    bool operator!=(Point other) const;

    double x;
    double y;
};

Point operator*(double scalar, Point other);

#endif //POINT_H
