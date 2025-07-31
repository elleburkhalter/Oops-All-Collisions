#ifndef MULTILEVELGRID_H
#define MULTILEVELGRID_H

#include <data_structures/ContainerInterface.h>

class MultiLevelGrid final : public ContainerInterface
{
public:
    MultiLevelGrid() = default;

private:
    class MLGNode
    {
    public:
        // ----- Checkers -----
        [[nodiscard]] bool is_root() const { return parent == nullptr; }
        [[nodiscard]] bool is_leaf() const { return ul_child == nullptr; }  // all four children should be assigned at once.

        // ----- Getters -----
        [[nodiscard]] MLGNode* get_parent() const { return parent.get(); }

        static constexpr size_t SPLIT_SIZE = 10;
    private:
        std::unique_ptr<MLGNode> parent = nullptr;

        std::unique_ptr<MLGNode> ul_child = nullptr;
        std::unique_ptr<MLGNode> ur_child = nullptr;
        std::unique_ptr<MLGNode> bl_child = nullptr;
        std::unique_ptr<MLGNode> br_child = nullptr;

        std::vector<EntityInterface*> entities{SPLIT_SIZE};

        BoundingBox bounding_box;
    };
};

#endif //MULTILEVELGRID_H
