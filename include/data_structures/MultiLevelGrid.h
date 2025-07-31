#ifndef MULTILEVELGRID_H
#define MULTILEVELGRID_H

#include <data_structures/ContainerInterface.h>

#include <utility>
#include <stack>

class MultiLevelGrid final : public ContainerInterface
{
public:
    MultiLevelGrid() = default;

private:
    class MLGNode : std::enable_shared_from_this<MLGNode>
    {
    public:
        explicit MLGNode(BoundingBox bounding_box): bounding_box(std::move(bounding_box)) {};

        // ----- Checkers -----
        [[nodiscard]] bool is_root() const { return parent.expired(); }
        [[nodiscard]] bool is_leaf() const { return ul_child == nullptr; }  // all four children should be assigned at once.
        [[nodiscard]] bool is_full() const { return entities.size() == SPLIT_SIZE; }
        [[nodiscard]] inline bool is_contained(const BoundingBox& bbox) const;
        [[nodiscard]] inline bool is_contained(Point point) const;

        // ----- Getters -----
        [[nodiscard]] std::weak_ptr<MLGNode> get_parent() const { return parent; }
        [[nodiscard]] std::weak_ptr<MLGNode> get_root();

        void insert(EntityInterface& entity);

        static constexpr size_t SPLIT_SIZE = 10;
    private:
        bool insert_recursive(EntityInterface& entity);

        std::shared_ptr<MLGNode> raise_root(bool expand_left, bool expand_up);;
        void split_node();

        std::weak_ptr<MLGNode> parent{};

        std::shared_ptr<MLGNode> ul_child = nullptr;
        std::shared_ptr<MLGNode> ur_child = nullptr;
        std::shared_ptr<MLGNode> bl_child = nullptr;
        std::shared_ptr<MLGNode> br_child = nullptr;

        std::list<EntityInterface*> entities{};

        BoundingBox bounding_box;

    };

    class iterator
    {
    public:
        using _iter = std::list<EntityInterface*>::const_iterator;

        using iterator_category = std::forward_iterator_tag;
        using value_type = EntityInterface*;      // what is stored in the container
        using reference = EntityInterface*;       // what operator* returns
        using pointer = EntityInterface**;        // operator-> returns a pointer-to-pointer
        using difference_type = std::ptrdiff_t;

        iterator()
        {
            to_visit.emplace();
        };
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        iterator(iterator&&) noexcept = default;
        iterator& operator=(iterator&&) noexcept = default;
        ~iterator() noexcept = default;

    private:

        std::stack<MLGNode*> to_visit{};

        void skip_empty()
        {

        }


    };
};

#endif //MULTILEVELGRID_H
