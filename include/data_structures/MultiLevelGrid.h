#ifndef MULTILEVELGRID_H
#define MULTILEVELGRID_H

#include <data_structures/ContainerInterface.h>

#include <utility>

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

        // ----- Getters -----
        [[nodiscard]] std::weak_ptr<MLGNode> get_parent() const { return parent; }

        static constexpr size_t SPLIT_SIZE = 10;
    private:
        std::shared_ptr<MLGNode> raise_root(bool expand_left, bool expand_up);;
        void split_node();

        std::weak_ptr<MLGNode> parent{};

        std::shared_ptr<MLGNode> ul_child = nullptr;
        std::shared_ptr<MLGNode> ur_child = nullptr;
        std::shared_ptr<MLGNode> bl_child = nullptr;
        std::shared_ptr<MLGNode> br_child = nullptr;

        std::vector<EntityInterface*> entities{SPLIT_SIZE};

        BoundingBox bounding_box;
    };
};

#endif //MULTILEVELGRID_H
