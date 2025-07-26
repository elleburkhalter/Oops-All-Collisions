#include <spatial/BoundingBox.h>

inline bool BoundingBox::contains(const Point p) const
{
    return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}
