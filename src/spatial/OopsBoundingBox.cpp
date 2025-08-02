#include <spatial/OopsBoundingBox.h>

inline Point OopsBoundingBox::get_centroid() const
{
    return {0.5*(min.x + max.x), 0.5*(min.y + max.y)};
}

inline bool OopsBoundingBox::contains(const Point p) const
{
    return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}

inline double OopsBoundingBox::get_height() const
{
    return max.y - min.y;
}

inline double OopsBoundingBox::get_width() const
{
    return max.x - min.x;
}

inline Point OopsBoundingBox::get_ul() const
{
    return min;
}
inline Point OopsBoundingBox::get_br() const
{
    return max;
}
inline Point OopsBoundingBox::get_bl() const
{
    return {min.x, max.y};
}
inline Point OopsBoundingBox::get_ur() const
{
    return {max.x, min.y};
}

