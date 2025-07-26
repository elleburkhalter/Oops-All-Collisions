#ifndef BALL_H
#define BALL_H

#include <spatial/Point.h>
#include <spatial/RegionInterface.h>

struct Ball final : RegionInterface
{
    Ball(): radius(0.0) {};
    Ball(const Point center, const double radius): center(center), radius(radius) {};
    Ball(const double x, const double y, const double r): center(x, y), radius(r) {};

    [[nodiscard]] inline bool contains(Point p) const override;

    Point center;
    double radius;
};

#endif //BALL_H
