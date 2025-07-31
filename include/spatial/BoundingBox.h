#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <spatial/Point.h>
#include <spatial/RegionInterface.h>

struct BoundingBox final : RegionInterface
{
    BoundingBox() = default;
    BoundingBox(const Point min, const Point max): min(min), max(max) {};
    BoundingBox(const double min_x, const double min_y, const double max_x, const double max_y): min(min_x, min_y), max(max_x, max_y) {};

    // ----- Checkers -----
    [[nodiscard]] inline bool contains(Point p) const override;

    // ----- Getters -----
    [[nodiscard]] inline Point get_centroid() const override;
    [[nodiscard]] inline double get_width() const;
    [[nodiscard]] inline double get_height() const;

    [[nodiscard]] inline Point get_ul() const;
    [[nodiscard]] inline Point get_br() const;
    [[nodiscard]] inline Point get_ur() const;
    [[nodiscard]] inline Point get_bl() const;

    Point min;
    Point max;
};

#endif //BOUNDINGBOX_H
