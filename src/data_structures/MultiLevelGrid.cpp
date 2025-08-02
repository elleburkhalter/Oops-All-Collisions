#include <range/v3/view/subrange.hpp>
#include <data_structures/MultiLevelGrid.h>

// TODO: MLG Implementation


void MultiLevelGrid::MLGNode::split_node()
{
    if (!is_leaf()) throw std::runtime_error("Tried to split non-leaf node.");

    const Point center = bounding_box.get_centroid();
    const OopsBoundingBox ul_bbox{bounding_box.min.x, bounding_box.min.y, center.x, center.y};
    const OopsBoundingBox ur_bbox{center.x, bounding_box.min.y, bounding_box.max.x, center.y};
    const OopsBoundingBox bl_bbox{bounding_box.min.x, center.y, center.x, bounding_box.max.y};
    const OopsBoundingBox br_bbox{center.x, center.y, bounding_box.max.x, bounding_box.max.y};

    ul_child = std::make_shared<MLGNode>(ul_bbox);
    ur_child = std::make_shared<MLGNode>(ur_bbox);
    bl_child = std::make_shared<MLGNode>(bl_bbox);
    br_child = std::make_shared<MLGNode>(br_bbox);

    ul_child->parent = shared_from_this();
    ur_child->parent = shared_from_this();
    bl_child->parent = shared_from_this();
    br_child->parent = shared_from_this();

    std::list<EntityInterface*> new_entities{SPLIT_SIZE};
    for (auto* entity : entities)
    {
        const bool success = ul_child->insert_recursive(*entity) ||
            ur_child->insert_recursive(*entity) ||
            bl_child->insert_recursive(*entity) ||
            br_child->insert_recursive(*entity);
        if (!success) new_entities.push_back(entity);
    }
    entities = std::move(new_entities);
}
std::shared_ptr<MultiLevelGrid::MLGNode> MultiLevelGrid::MLGNode::raise_root(const bool expand_left, const bool expand_up)
{
    if (!is_root()) throw std::runtime_error("Tried to raise non-root node.");

    const uint8_t expand_idx = expand_left + (expand_up << 1);

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
    default:
        break;
    }

    const OopsBoundingBox p_bbox = {{p_center.x - bounding_box.get_width(), p_center.y - bounding_box.get_height()}, {p_center.x + bounding_box.get_width(), p_center.y + bounding_box.get_height()}};

    const OopsBoundingBox ul_bbox{p_bbox.min.x, p_bbox.min.y, p_center.x, p_center.y};
    const OopsBoundingBox ur_bbox{p_center.x, p_bbox.min.y, p_bbox.max.x, p_center.y};
    const OopsBoundingBox bl_bbox{p_bbox.min.x, p_center.y, p_center.x, p_bbox.max.y};
    const OopsBoundingBox br_bbox{p_center.x, p_center.y, p_bbox.max.x, p_bbox.max.y};

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
    default:
        break;
    }

    new_root->ul_child->parent = new_root;
    new_root->ur_child->parent = new_root;
    new_root->bl_child->parent = new_root;
    new_root->br_child->parent = new_root;

    return new_root;
}

std::weak_ptr<MultiLevelGrid::MLGNode> MultiLevelGrid::MLGNode::get_root()
{
    std::weak_ptr<MLGNode> root = shared_from_this();
    while (true)
    {
        if (const auto locked = root.lock())
        {
            if (locked->is_root()) break;
            root = locked->get_parent();
        }
    }
    return root;
}

inline bool MultiLevelGrid::MLGNode::contains(const OopsBoundingBox& bbox) const
{
    return this->bounding_box.min.x <= bbox.min.x &&
        this->bounding_box.max.x >= bbox.max.x &&
        this->bounding_box.min.y <= bbox.min.y &&
        this->bounding_box.max.y >= bbox.max.y;
}

inline bool MultiLevelGrid::MLGNode::contains(const Point point) const
{
    return this->bounding_box.contains(point);
}


bool MultiLevelGrid::MLGNode::insert_recursive(EntityInterface& entity)
{
    if (!contains(entity.get_collider().get_bounding_box())) return false;
    if (is_leaf() && !is_full())
    {
        entities.push_back(&entity);
        entity.set_tag<MLGNode>(shared_from_this());
        return true;
    }
    if (is_leaf())
    {
        split_node();
    }
    if (ul_child->insert_recursive(entity) ||
        ur_child->insert_recursive(entity) ||
        bl_child->insert_recursive(entity) ||
        br_child->insert_recursive(entity))
        return true;

    entities.push_back(&entity);
    entity.set_tag<MLGNode>(shared_from_this());
    return true;

}

void MultiLevelGrid::MLGNode::insert(EntityInterface& entity)
{
    std::weak_ptr<MLGNode> root = get_root();
    auto locked = root.lock();
    if (!locked) return;

    while (!locked->contains(entity.get_collider().get_bounding_box().min))
    {
        root = raise_root(true, true);
        locked = root.lock();
        if (!locked) return;
    }
    while (!locked->contains(entity.get_collider().get_bounding_box().max))
    {
        root = raise_root(false, false);
        locked = root.lock();
        if (!locked) return;
    }
    locked->insert_recursive(entity);
}


MultiLevelGrid::MLGNode::iterator MultiLevelGrid::MLGNode::begin() const
{
    return iterator(*this);
}
MultiLevelGrid::MLGNode::iterator MultiLevelGrid::MLGNode::end()
{
    return iterator();
}

MultiLevelGrid::MLGNode::iterator MultiLevelGrid::begin() const
{
    return root.begin();
}
MultiLevelGrid::MLGNode::iterator MultiLevelGrid::end() const
{
    return root.end();
}
void MultiLevelGrid::add_collider(EntityInterface& other)
{
    ++entity_count;
    root.insert(other);
    const auto new_root = root.get_root().lock();
    root = *new_root;
}
void MultiLevelGrid::reserve_slots(size_t n)
{

}
ranges::any_view<EntityInterface*> MultiLevelGrid::get_all_entities() const
{
    auto range = ranges::subrange(this->begin(), this->end());
    return ranges::any_view<EntityInterface*>{range};
}
std::list<EntityInterface*> MultiLevelGrid::MLGNode::coarse_collision_recursive(const OopsBoundingBox& bbox) const
{
    std::list<EntityInterface*> collisions{};
    if (contains(bbox)) collisions = this->entities;
    if (contains(bbox) && !is_leaf())
    {
        collisions.splice(collisions.end(), ul_child->coarse_collision_recursive(bbox));
        collisions.splice(collisions.end(), ur_child->coarse_collision_recursive(bbox));
        collisions.splice(collisions.end(), bl_child->coarse_collision_recursive(bbox));
        collisions.splice(collisions.end(), br_child->coarse_collision_recursive(bbox));
    }
    return collisions;
}

std::vector<EntityInterface*> MultiLevelGrid::get_collisions(const EntityInterface& other) const
{
    std::vector<EntityInterface*> collisions{6};
    const ColliderInterface& collider = other.get_collider();
    const OopsBoundingBox bbox = collider.get_bounding_box();

    for (const std::list<EntityInterface*> candidates = this->root.coarse_collision_recursive(bbox); auto* candidate : candidates)
    {
        if (other.get_collider().is_colliding_with(candidate->get_collider())) collisions.push_back(candidate);
    }
    return collisions;
}

size_t MultiLevelGrid::get_entity_count() const
{
    return entity_count;
}

void MultiLevelGrid::MLGNode::delete_children()
{
    this->ul_child = nullptr;
    this->ur_child = nullptr;
    this->bl_child = nullptr;
    this->br_child = nullptr;
}


void MultiLevelGrid::update_structure()
{
    for (MLGNode::iterator it = begin(); it != end(); ++it)
    {
        EntityInterface* entity = *it;
        MLGNode container = *(entity->get_tag<MLGNode>());
        // If container no longer contains entity; reinsert from root
        if (!container.contains(entity->get_collider().get_bounding_box()))
        {
            container.get_entities().erase(it.get_inner());
            add_collider(*entity);
            // If rebinding the entity makes the parent of the container able to delete its children; do so.
            if (const auto parent = container.get_parent().lock(); parent && parent->can_delete_children())
            {
                parent->delete_children();
            }
            continue;
        }
        // If container has children, see if any children fully encapsulate
        if (!container.is_leaf())
        {
            if (const std::shared_ptr<MLGNode> child = container.get_ul_child(); child && child->insert_recursive(*entity))
            {
                container.get_entities().erase(it.get_inner());
                continue;
            }
            if (const std::shared_ptr<MLGNode> child = container.get_ur_child(); child && child->insert_recursive(*entity))
            {
                container.get_entities().erase(it.get_inner());
                continue;
            }
            if (const std::shared_ptr<MLGNode> child = container.get_bl_child(); child && child->insert_recursive(*entity))
            {
                container.get_entities().erase(it.get_inner());
                continue;
            }
            if (const std::shared_ptr<MLGNode> child = container.get_br_child(); child && child->insert_recursive(*entity))
            {
                container.get_entities().erase(it.get_inner());
                continue;
            }
        }
        // otherwise nothing changes!
    }
}

