#include <spatial/BoundingBox.h>

inline Point BoundingBox::get_centroid() const
{
    return {0.5*(min.x + max.x), 0.5*(min.y + max.y)};
}

inline bool BoundingBox::contains(const Point p) const
{
    return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}
