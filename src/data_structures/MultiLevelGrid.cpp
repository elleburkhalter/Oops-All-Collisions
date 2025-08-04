#include <range/v3/view/subrange.hpp>
#include <data_structures/MultiLevelGrid.h>

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

    std::list<EntityInterface*> new_entities{};
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

std::shared_ptr<MultiLevelGrid::MLGNode> MultiLevelGrid::MLGNode::raise_root(
    const bool expand_left, const bool expand_up)
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

    const OopsBoundingBox p_bbox = {
        {p_center.x - bounding_box.get_width(), p_center.y - bounding_box.get_height()},
        {p_center.x + bounding_box.get_width(), p_center.y + bounding_box.get_height()}
    };

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
    std::weak_ptr<MLGNode> new_root = shared_from_this();
    while (true)
    {
        if (const auto locked = new_root.lock())
        {
            if (locked->is_root()) break;
            new_root = locked->get_parent();
        }
    }
    return new_root;
}

bool MultiLevelGrid::MLGNode::contains(const OopsBoundingBox& bbox) const
{
    return this->bounding_box.min.x <= bbox.min.x &&
        this->bounding_box.max.x >= bbox.max.x &&
        this->bounding_box.min.y <= bbox.min.y &&
        this->bounding_box.max.y >= bbox.max.y;
}

bool MultiLevelGrid::MLGNode::contains(const Point point) const
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

std::shared_ptr<MultiLevelGrid::MLGNode> MultiLevelGrid::MLGNode::insert(EntityInterface& entity)
{
    // std::weak_ptr<MLGNode> new_root = get_root();
    // auto current = new_root.lock();

    std::shared_ptr<MLGNode> current = shared_from_this();;
    if (!current) return nullptr;

    const OopsBoundingBox bbox = entity.get_collider().get_bounding_box();
    while (!current->contains(bbox))
    {
        const bool expand_left = bbox.min.x < current->bounding_box.min.x;
        const bool expand_up = bbox.min.y < current->bounding_box.min.y;
        const bool expand_right = bbox.max.x > current->bounding_box.max.x;
        const bool expand_down = bbox.max.y > current->bounding_box.max.y;

        if (expand_left || expand_up)
        {
            current = current->raise_root(expand_left, expand_up);
        }
        else
        {
            current = current->raise_root(!expand_right, !expand_down);
        }
    }
    current->insert_recursive(entity);
    return current;
}


MultiLevelGrid::MLGNode::iterator MultiLevelGrid::MLGNode::begin() const
{
    return iterator(shared_from_this()); // const overload yields shared_ptr<const MLGNode>
}

MultiLevelGrid::MLGNode::iterator MultiLevelGrid::MLGNode::end()
{
    return iterator(); // default-constructed -> at_end_ = true
}

MultiLevelGrid::MLGNode::iterator MultiLevelGrid::begin() const
{
    return root->begin();
}

MultiLevelGrid::MLGNode::iterator MultiLevelGrid::end() const
{
    return root->end();
}

void MultiLevelGrid::add_collider(EntityInterface& other)
{
    ++entity_count;
    if (const std::shared_ptr<MLGNode> potential_root = root->insert(other)) root = std::move(potential_root);
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
    std::vector<EntityInterface*> collisions{};
    collisions.reserve(6);
    const ColliderInterface& collider = other.get_collider();
    const OopsBoundingBox bbox = collider.get_bounding_box();

    for (const std::list<EntityInterface*> candidates = this->root->coarse_collision_recursive(bbox); EntityInterface*
         candidate : candidates)
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
    std::vector<EntityInterface*> snapshot;
    snapshot.reserve(entity_count);
    {
        std::stack<std::shared_ptr<MLGNode>> st;
        st.push(root);
        while (!st.empty())
        {
            const auto n = std::move(st.top());
            st.pop();

            for (EntityInterface* e : n->entities)
            {
                if (e) snapshot.push_back(e);
            }

            // DFS to children
            if (!n->is_leaf())
            {
                if (n->ul_child) st.push(n->ul_child);
                if (n->ur_child) st.push(n->ur_child);
                if (n->bl_child) st.push(n->bl_child);
                if (n->br_child) st.push(n->br_child);
            }
        }
    }

    // Parents to consider for collapsing after the moves.
    std::vector<std::weak_ptr<MLGNode>> maybe_collapse;
    maybe_collapse.reserve(snapshot.size());

    auto erase_from_node = [&](const std::shared_ptr<MLGNode>& node, const EntityInterface* entity)
    {
        if (!node) return;
        for (auto it = node->entities.begin(); it != node->entities.end(); ++it)
        {
            if (*it == entity)
            {
                node->entities.erase(it); // safe for std::list: only invalidates 'it'
                if (const auto p = node->get_parent().lock())
                {
                    maybe_collapse.emplace_back(p);
                }
                return;
            }
        }
    };

    for (EntityInterface* entity : snapshot)
    {
        if (!entity) continue;

        auto container = entity->get_tag<MLGNode>();
        if (!container) continue; // entity might have been removed externally

        const OopsBoundingBox& bbox = entity->get_collider().get_bounding_box();
        if (!container->contains(bbox))
        {
            // Remove from old node
            erase_from_node(container, entity);

            // Reinsert (may raise root)
            if (auto new_root = root->insert(*entity))
            {
                root = std::move(new_root);
            }
            continue;
        }

        // Still inside container: try to push down to a child that fully contains it.
        if (!container->is_leaf())
        {
            bool moved = false;
            if (auto c = container->get_ul_child(); c && c->insert_recursive(*entity)) moved = true;
            else if (auto c = container->get_ur_child(); c && c->insert_recursive(*entity)) moved = true;
            else if (auto c = container->get_bl_child(); c && c->insert_recursive(*entity)) moved = true;
            else if (auto c = container->get_br_child(); c && c->insert_recursive(*entity)) moved = true;

            if (moved)
            {
                // Remove from old node after successful child insertion
                erase_from_node(container, entity);
            }
        }
        // else leave in place
    }

    // Collapse any parents whose children became empty (after all erasures).
    for (auto& wparent : maybe_collapse)
    {
        if (auto parent = wparent.lock(); parent && parent->can_delete_children())
        {
            parent->delete_children();
        }
    }
}

void MultiLevelGrid::MLGNode::draw_debug(RendererInterface& renderer) const
{
    renderer.draw_box(this->bounding_box);
    if (!this->is_leaf())
    {
        this->ul_child->draw_debug(renderer);
        this->ur_child->draw_debug(renderer);
        this->bl_child->draw_debug(renderer);
        this->br_child->draw_debug(renderer);
    }
}

void MultiLevelGrid::draw_debug(RendererInterface& renderer) const
{
    size_t count = 0;
    for (const EntityInterface* entity : this->get_all_entities())
    {
        renderer.draw_entity(*entity);
    }
    this->root->draw_debug(renderer);
}
