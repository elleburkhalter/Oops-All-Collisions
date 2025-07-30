#ifndef NAIVELINEAR_H
#define NAIVELINEAR_H

#include <vector>
#include <data_structures/ContainerInterface.h>

// This is intentionally slow and bad (O(n^2)) used for SMALL cases for comparison
class NaiveLinear final : public ContainerInterface
{
public:
    NaiveLinear() = default;
    [[nodiscard]] std::vector<ColliderInterface&> get_collisions(const ColliderInterface& other) const override;

    void reserve_slots(size_t n) override;
    void add_collider(ColliderInterface& other) override;
    void update_structure() override;

private:
    std::vector<ColliderInterface&> colliders{};

};

#endif //NAIVELINEAR_H
