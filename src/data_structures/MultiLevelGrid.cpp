#include <data_structures/MultiLevelGrid.h>

// TODO: MLG Implementation


void MultiLevelGrid::MLGNode::split_node()
{
    if (!is_leaf()) throw std::runtime_error("Tried to split non-leaf node.");

    const Point center = bounding_box.get_centroid();
    const BoundingBox ul_bbox{bounding_box.min.x, bounding_box.min.y, center.x, center.y};
    const BoundingBox ur_bbox{center.x, bounding_box.min.y, bounding_box.max.x, center.y};
    const BoundingBox bl_bbox{bounding_box.min.x, center.y, center.x, bounding_box.max.y};
    const BoundingBox br_bbox{center.x, center.y, bounding_box.max.x, bounding_box.max.y};

    ul_child = std::make_shared<MLGNode>(ul_bbox);
    ur_child = std::make_shared<MLGNode>(ur_bbox);
    bl_child = std::make_shared<MLGNode>(bl_bbox);
    br_child = std::make_shared<MLGNode>(br_bbox);

    ul_child->parent = shared_from_this();
    ur_child->parent = shared_from_this();
    bl_child->parent = shared_from_this();
    br_child->parent = shared_from_this();

}
std::shared_ptr<MultiLevelGrid::MLGNode> MultiLevelGrid::MLGNode::raise_root(const bool expand_left, const bool expand_up)
{
    if (!is_root()) throw std::runtime_error("Tried to raise non-root node.");

    const uint8_t expand_idx = expand_left + expand_up << 1;

    Point p_center;

    switch (expand_idx)
    {
    case 0: // go rightwards and downwards (we have ul)
        p_center = bounding_box.max;
        break;
    case 1: // go leftwards and downwards (we have ur)
        p_center = {bounding_box.min.x, bounding_box.max.y};
        break;
    case 2: // go rightwards and upwards (we have bl)
        p_center = {bounding_box.max.x, bounding_box.min.y};
        break;
    case 3: // go leftwards and upwards (we have br)
        p_center = bounding_box.min;
        break;
    }

    const BoundingBox p_bbox = {{p_center.x - bounding_box.get_width(), p_center.y - bounding_box.get_height()}, {p_center.x + bounding_box.get_width(), p_center.y + bounding_box.get_height()}};

    const BoundingBox ul_bbox{p_bbox.min.x, p_bbox.min.y, p_center.x, p_center.y};
    const BoundingBox ur_bbox{p_center.x, p_bbox.min.y, p_bbox.max.x, p_center.y};
    const BoundingBox bl_bbox{p_bbox.min.x, p_center.y, p_center.x, p_bbox.max.y};
    const BoundingBox br_bbox{p_center.x, p_center.y, p_bbox.max.x, p_bbox.max.y};

    const auto new_root = std::make_shared<MLGNode>(p_bbox);

    switch (expand_idx)
    {
    case 0: // go rightwards and downwards (we have ul)
        new_root->ul_child = shared_from_this();
        new_root->ur_child = std::make_shared<MLGNode>(ur_bbox);
        new_root->bl_child = std::make_shared<MLGNode>(bl_bbox);
        new_root->br_child = std::make_shared<MLGNode>(br_bbox);
        break;
    case 1: // go leftwards and downwards (we have ur)
        new_root->ul_child = std::make_shared<MLGNode>(ul_bbox);
        new_root->ur_child = shared_from_this();
        new_root->bl_child = std::make_shared<MLGNode>(bl_bbox);
        new_root->br_child = std::make_shared<MLGNode>(br_bbox);
        break;
    case 2: // go rightwards and upwards (we have bl)
        new_root->ul_child = std::make_shared<MLGNode>(ul_bbox);
        new_root->ur_child = std::make_shared<MLGNode>(ur_bbox);
        new_root->bl_child = shared_from_this();
        new_root->br_child = std::make_shared<MLGNode>(br_bbox);
        break;
    case 3: // go leftwards and upwards (we have br)
        new_root->ul_child = std::make_shared<MLGNode>(ul_bbox);
        new_root->ur_child = std::make_shared<MLGNode>(ur_bbox);
        new_root->bl_child = std::make_shared<MLGNode>(bl_bbox);
        new_root->br_child = shared_from_this();
        break;
    }

    new_root->ul_child->parent = new_root;
    new_root->ur_child->parent = new_root;
    new_root->bl_child->parent = new_root;
    new_root->br_child->parent = new_root;

    return new_root;
}

