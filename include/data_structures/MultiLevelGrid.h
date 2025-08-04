#ifndef MULTILEVELGRID_H
#define MULTILEVELGRID_H

#include <data_structures/ContainerInterface.h>

#include <utility>
#include <stack>
#include <list>
#include <constants.h>
#include <unordered_set>

class MultiLevelGrid final : public ContainerInterface
{
    class MLGNode final : public DebugDrawableInterface, public std::enable_shared_from_this<MLGNode>
    {
    public:
        class iterator;
        MLGNode() = delete;

        explicit MLGNode(OopsBoundingBox bounding_box): bounding_box(std::move(bounding_box))
        {
        };

        // ----- Checkers -----
        [[nodiscard]] bool is_root() const { return parent.expired(); }
        [[nodiscard]] bool is_leaf() const { return ul_child == nullptr; }
        // all four children should be assigned at once.
        [[nodiscard]] bool is_full() const { return entities.size() == SPLIT_SIZE; }
        [[nodiscard]] bool is_empty() const { return (is_leaf() && entities.empty()); }

        [[nodiscard]] bool can_delete_children() const
        {
            return !is_leaf() && ul_child->is_empty() && ur_child->is_empty() && bl_child->is_empty() && br_child->
                is_empty();
        }

        [[nodiscard]] bool contains(const OopsBoundingBox& bbox) const;
        [[nodiscard]] bool contains(Point point) const;

        // ----- Getters -----
        [[nodiscard]] std::weak_ptr<MLGNode> get_parent() const { return parent; }
        [[nodiscard]] std::weak_ptr<MLGNode> get_root();
        [[nodiscard]] std::shared_ptr<MLGNode> get_ul_child() const { return ul_child; }
        [[nodiscard]] std::shared_ptr<MLGNode> get_ur_child() const { return ur_child; }
        [[nodiscard]] std::shared_ptr<MLGNode> get_bl_child() const { return bl_child; }
        [[nodiscard]] std::shared_ptr<MLGNode> get_br_child() const { return br_child; }
        [[nodiscard]] std::list<EntityInterface*>& get_entities() { return entities; }
        [[nodiscard]] iterator begin() const;
        [[nodiscard]] static iterator end();

        std::shared_ptr<MLGNode> insert(EntityInterface& entity);
        std::list<EntityInterface*> coarse_collision_recursive(const OopsBoundingBox& bbox) const;
        bool insert_recursive(EntityInterface& entity);
        void delete_children();

        void draw_debug(RendererInterface& renderer) const override;

        static constexpr size_t SPLIT_SIZE = CELL_COUNT_SPLIT_THRESHOLD;

    private:
        std::shared_ptr<MLGNode> raise_root(bool expand_left, bool expand_up);;
        void split_node();

        std::weak_ptr<MLGNode> parent{};

        friend MultiLevelGrid;
        std::shared_ptr<MLGNode> ul_child = nullptr;
        std::shared_ptr<MLGNode> ur_child = nullptr;
        std::shared_ptr<MLGNode> bl_child = nullptr;
        std::shared_ptr<MLGNode> br_child = nullptr;

        std::list<EntityInterface*> entities{};

        OopsBoundingBox bounding_box{};

    public:
        class iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = EntityInterface*;
    using reference         = EntityInterface*;         // return by value
    using pointer           = EntityInterface* const*;  // &(*inner_it)
    using difference_type   = std::ptrdiff_t;

    iterator() : at_end_(true) {}

    explicit iterator(std::shared_ptr<const MLGNode> root_sp) {
        if (root_sp) to_visit.push(std::move(root_sp));
        advance_to_next_valid();
    }

    reference operator*() const {
        // Guaranteed valid when !at_end_ and inner_it != end()
        return *inner_it; // EntityInterface*
    }

    pointer operator->() const {
        return &(*inner_it); // EntityInterface* const*
    }

    iterator& operator++() {
        if (at_end_) return *this;
        ++inner_it;
        // skip nulls in this node
        while (inner_it != current_node->entities.end() && *inner_it == nullptr) ++inner_it;
        if (inner_it == current_node->entities.end()) {
            advance_to_next_valid();
        }
        return *this;
    }

    iterator operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const iterator& other) const {
        if (at_end_ && other.at_end_) return true;
        if (at_end_ != other.at_end_) return false;
        return current_node.get() == other.current_node.get()
            && inner_it == other.inner_it;
    }
    bool operator!=(const iterator& other) const { return !(*this == other); }

    [[nodiscard]] std::list<EntityInterface*>::const_iterator get_inner() const { return inner_it; }
    [[nodiscard]] std::list<EntityInterface*>::const_iterator get_inner_end() const {
        return current_node ? current_node->entities.end()
                            : std::list<EntityInterface*>::const_iterator{};
    }
    [[nodiscard]] const MLGNode* get_owner() const { return current_node.get(); }

private:
    // Keep children alive even if unlinked from their parent
    std::stack<std::shared_ptr<const MLGNode>> to_visit;
    std::shared_ptr<const MLGNode> current_node{};
    std::list<EntityInterface*>::const_iterator inner_it{};
    bool at_end_ = false;

    void advance_to_next_valid() {
        while (!to_visit.empty()) {
            current_node = std::move(to_visit.top());
            to_visit.pop();

            // DFS push: BR, BL, UR, UL (reverse of visit order)
            if (!current_node->is_leaf()) {
                if (current_node->br_child) to_visit.push(current_node->br_child);
                if (current_node->bl_child) to_visit.push(current_node->bl_child);
                if (current_node->ur_child) to_visit.push(current_node->ur_child);
                if (current_node->ul_child) to_visit.push(current_node->ul_child);
            }

            inner_it = current_node->entities.begin();
            // skip nulls in this node
            while (inner_it != current_node->entities.end() && *inner_it == nullptr) ++inner_it;

            if (inner_it != current_node->entities.end()) {
                at_end_ = false;
                return;
            }
            // else: node has no non-null entities — continue
        }

        // No more nodes with entities: canonical end iterator
        current_node.reset();
        inner_it = {};
        at_end_ = true;
    }
};
    };

public:
    MultiLevelGrid()
    {
        root = std::make_shared<MLGNode>(OopsBoundingBox{X_START_MIN, Y_START_MIN, X_START_MAX, Y_START_MAX});
    };

    std::vector<EntityInterface*> get_collisions(const EntityInterface& other) const override;
    ranges::any_view<EntityInterface*> get_all_entities() const override;
    size_t get_entity_count() const override;

    void reserve_slots(size_t n) override;
    void add_collider(EntityInterface& other) override;
    void update_structure() override;

    void draw_debug(RendererInterface& renderer) const override;

    MLGNode::iterator begin() const;
    MLGNode::iterator end() const;

    static constexpr double X_START_MIN = MULTILEVELGRID_INITIAL_X_START;
    static constexpr double X_START_MAX = MULTILEVELGRID_INITIAL_X_END;
    static constexpr double Y_START_MIN = MULTILEVELGRID_INITIAL_Y_START;
    static constexpr double Y_START_MAX = MULTILEVELGRID_INITIAL_Y_END;

    size_t entity_count = 0;

private:
    std::shared_ptr<MLGNode> root;
};

#endif //MULTILEVELGRID_H
