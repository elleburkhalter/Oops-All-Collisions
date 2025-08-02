#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <spatial/Point.h>
#include <spatial/RegionInterface.h>

struct OopsBoundingBox final : RegionInterface
{
    OopsBoundingBox() = default;
    OopsBoundingBox(const Point min, const Point max): min(min), max(max) {};
    OopsBoundingBox(const double min_x, const double min_y, const double max_x, const double max_y): min(min_x, min_y), max(max_x, max_y) {};

    // ----- Checkers -----
    [[nodiscard]] bool contains(Point p) const override;

    // ----- Getters -----
    [[nodiscard]] Point get_centroid() const override;
    [[nodiscard]] double get_width() const;
    [[nodiscard]] double get_height() const;

    [[nodiscard]] Point get_ul() const;
    [[nodiscard]] Point get_br() const;
    [[nodiscard]] Point get_ur() const;
    [[nodiscard]] Point get_bl() const;

    Point min;
    Point max;
};

#endif //BOUNDINGBOX_H
