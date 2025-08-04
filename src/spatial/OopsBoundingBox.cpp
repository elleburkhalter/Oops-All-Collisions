#include <spatial/OopsBoundingBox.h>

Point OopsBoundingBox::get_centroid() const
{
    return {0.5*(min.x + max.x), 0.5*(min.y + max.y)};
}

bool OopsBoundingBox::contains(const Point p) const
{
    return min.x <= p.x &&
        max.x >= p.x &&
        min.y <= p.y &&
        max.y >= p.y;
}

double OopsBoundingBox::get_height() const
{
    return max.y - min.y;
}

double OopsBoundingBox::get_width() const
{
    return max.x - min.x;
}

Point OopsBoundingBox::get_ul() const
{
    return min;
}
Point OopsBoundingBox::get_br() const
{
    return max;
}
Point OopsBoundingBox::get_bl() const
{
    return {min.x, max.y};
}
Point OopsBoundingBox::get_ur() const
{
    return {max.x, min.y};
}
void OopsBoundingBox::draw_debug(RendererInterface& renderer) const
{
    renderer.draw_box(*this);
}

