#include <spatial/BoundingBox.h>

inline Point BoundingBox::get_centroid() const
{
    return {0.5*(min.x + max.x), 0.5*(min.y + max.y)};
}

inline bool BoundingBox::contains(const Point p) const
{
    return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}

inline double BoundingBox::get_height() const
{
    return max.y - min.y;
}

inline double BoundingBox::get_width() const
{
    return max.x - min.x;
}

inline Point BoundingBox::get_ul() const
{
    return min;
}
inline Point BoundingBox::get_br() const
{
    return max;
}
inline Point BoundingBox::get_bl() const
{
    return {min.x, max.y};
}
inline Point BoundingBox::get_ur() const
{
    return {max.x, min.y};
}

