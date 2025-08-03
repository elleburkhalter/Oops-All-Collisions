#ifndef NAIVELINEAR_H
#define NAIVELINEAR_H

#include <range/v3/view/any_view.hpp>
#include <vector>
#include <data_structures/ContainerInterface.h>

// This is intentionally slow and bad (O(n^2)) used for SMALL cases for comparison
class NaiveLinear final : public ContainerInterface
{
public:
    NaiveLinear() = default;

    // ----- Getters -----
    [[nodiscard]] std::vector<EntityInterface*> get_collisions(const EntityInterface& other) const override;
    [[nodiscard]] ranges::any_view<EntityInterface*> get_all_entities() const override;
    [[nodiscard]] size_t get_entity_count() const override;

    void reserve_slots(size_t n) override;
    void add_collider(EntityInterface& other) override;
    void update_structure() override;

    void draw_debug(RendererInterface& renderer) const override;

private:
    std::vector<EntityInterface*> entities{};

};

#endif //NAIVELINEAR_H
