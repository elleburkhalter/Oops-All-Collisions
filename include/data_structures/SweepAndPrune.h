#ifndef SWEEPANDPRUNE_H
#define SWEEPANDPRUNE_H
#include <list>
#include <range/v3/view/any_view.hpp>
#include <data_structures/ContainerInterface.h>

class SweepAndPrune final : public ContainerInterface
{
public:
    SweepAndPrune() = default;

    // ----- Getters -----
    // Note that single collision checks are not supported!
    [[nodiscard]] std::list<std::pair<EntityInterface*, EntityInterface*>> get_all_collisions() const override;
    [[nodiscard]] ranges::any_view<EntityInterface*> get_all_entities() const override;
    [[nodiscard]] size_t get_entity_count() const override;

    // ----- Initialization -----
    void reserve_slots(size_t n) override;
    void add_collider(EntityInterface& other) override;
    void post_bulk_add_callback() override;
    void update_structure() override;

    void draw_debug(RendererInterface& renderer) const override;

private:
    struct SAPLocation
    {
        SAPLocation(EntityInterface& referer, const bool is_begin): referer(&referer), is_begin(is_begin)
        {
            const OopsBoundingBox bbox = referer.get_collider().get_bounding_box();
            is_begin ? location = bbox.min.x : location = bbox.max.x;
        }
        std::unique_ptr<EntityInterface> referer;
        double location = 0.0;
        bool is_begin = true;
    };

    std::vector<SAPLocation> entities{};
};

#endif //SWEEPANDPRUNE_H
