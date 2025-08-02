#ifndef MULTILEVELGRID_H
#define MULTILEVELGRID_H

#include <data_structures/ContainerInterface.h>

#include <utility>
#include <stack>

class MultiLevelGrid final : public ContainerInterface
{
class MLGNode : std::enable_shared_from_this<MLGNode>
    {
    public:
        class iterator;
        MLGNode() = delete;
        explicit MLGNode(OopsBoundingBox bounding_box): bounding_box(std::move(bounding_box)) {};

        // ----- Checkers -----
        [[nodiscard]] bool is_root() const { return parent.expired(); }
        [[nodiscard]] bool is_leaf() const { return ul_child == nullptr; }  // all four children should be assigned at once.
        [[nodiscard]] bool is_full() const { return entities.size() == SPLIT_SIZE; }
        [[nodiscard]] bool is_empty() const { return (is_leaf() && entities.empty()); }
        [[nodiscard]] bool can_delete_children() const { return !is_leaf() && ul_child->is_empty() && ur_child->is_empty() && bl_child->is_empty() && br_child->is_empty(); }
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

        void insert(EntityInterface& entity);
        std::list<EntityInterface*> coarse_collision_recursive(const OopsBoundingBox& bbox) const;
        bool insert_recursive(EntityInterface& entity);
        void delete_children();

        static constexpr size_t SPLIT_SIZE = 10;
    private:

        std::shared_ptr<MLGNode> raise_root(bool expand_left, bool expand_up);;
        void split_node();

        std::weak_ptr<MLGNode> parent{};

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
            using _iter = std::list<EntityInterface*>::const_iterator;

            using iterator_category = std::forward_iterator_tag;
            using value_type = EntityInterface*;      // what is stored in the container
            using reference = EntityInterface*;       // what operator* returns
            using pointer = EntityInterface**;        // operator-> returns a pointer-to-pointer
            using difference_type = std::ptrdiff_t;

            explicit iterator(const MLGNode& node)
            {
                to_visit = traverse(node);
                skip_empty();
            };

            iterator() = default;
            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            iterator(iterator&&) noexcept = default;
            iterator& operator=(iterator&&) noexcept = default;
            ~iterator() noexcept = default;

            [[nodiscard]] _iter get_inner() const { return inner; };

            // Now just return the pointer itself
            reference operator*() const { return *inner; }
            // For operator->, return address of the pointer in the list
            pointer operator->() const { return const_cast<pointer>(&(*inner)); }
            bool operator==(const iterator& other) const { return outer == other.outer && inner == other.inner; }
            bool operator!=(const iterator& other) const { return !(*this == other); }

            iterator& operator++()
            {
                ++inner;
                skip_empty();
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            void next_node()
            {
                if (to_visit.empty()) outer = nullptr;
                outer = to_visit.front();
                to_visit.pop_front();
            }

        private:

            std::list<const MLGNode*> to_visit{};
            const MLGNode* outer = nullptr;
            _iter inner{};

            static std::list<const MLGNode*> traverse(const MLGNode& node)
            {
                std::list<const MLGNode*> list{};
                const bool node_has_children = !node.is_leaf();
                if (node_has_children)
                {
                    list.splice(list.end(), traverse(*node.ul_child));
                    list.splice(list.end(), traverse(*node.ur_child));
                }
                list.emplace_back(&node);
                if (node_has_children)
                {
                    list.splice(list.end(), traverse(*node.bl_child));
                    list.splice(list.end(), traverse(*node.br_child));
                }
                return list;
            }

            void skip_empty()
            {
                while (outer != nullptr && inner == outer->entities.end())
                {
                    next_node();
                    if (outer != nullptr) inner = outer->entities.begin();
                }
            }


        };

    };

public:
    MultiLevelGrid() = default;

    std::vector<EntityInterface*> get_collisions(const EntityInterface& other) const override;
    ranges::any_view<EntityInterface*> get_all_entities() const override;
    size_t get_entity_count() const override;

    void reserve_slots(size_t n) override;
    void add_collider(EntityInterface& other) override;
    void update_structure() override;

    MLGNode::iterator begin() const;
    MLGNode::iterator end() const;

    static constexpr double X_START_MIN = -128.0;
    static constexpr double X_START_MAX = 128.0;
    static constexpr double Y_START_MIN = -128.0;
    static constexpr double Y_START_MAX = 128.0;

    size_t entity_count = 0;

private:
    MLGNode root{{X_START_MIN, Y_START_MIN, X_START_MAX, Y_START_MAX}};
};

#endif //MULTILEVELGRID_H
