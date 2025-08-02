#ifndef REGIONINTERFACE_H
#define REGIONINTERFACE_H

#include <spatial/Point.h>

struct RegionInterface
{
    virtual ~RegionInterface() = default;

    [[nodiscard]] virtual bool contains(Point p) const = 0;
    [[nodiscard]] virtual Point get_centroid() const = 0;
};

#endif //REGIONINTERFACE_H
