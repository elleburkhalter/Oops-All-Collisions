#include <range/v3/view/transform.hpp>
#include <range/v3/view/any_view.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/subrange.hpp>

#include <unordered_set>
#include <data_structures/SweepAndPrune.h>
#include <algorithm>

void SweepAndPrune::reserve_slots(const size_t n)
{
    this->entities.reserve(n * 2);
}
void SweepAndPrune::add_collider(EntityInterface& other)
{
    this->entities.emplace_back(other, true);
    this->entities.emplace_back(other, false);
}
void SweepAndPrune::post_bulk_add_callback()
{
    std::ranges::sort(this->entities,
        [](const SAPLocation& a, const SAPLocation& b) { return a.location < b.location; } );
}
void SweepAndPrune::update_structure()
{
    // Insertion sort is O(n) because structure should be nearly sorted.
    for (size_t i = 0; i < this->entities.size(); ++i)
    {
        SAPLocation temp = std::move(this->entities[i]);
        size_t j = i;
        while (j > 0 && this->entities[j-1].location > temp.location)
        {
            this->entities[j] = std::move(this->entities[j-1]);
            --j;
        }
        this->entities[j] = std::move(temp);
    }
}

ranges::any_view<EntityInterface*> SweepAndPrune::get_all_entities() const
{
    auto base_range = ranges::make_subrange(this->entities.begin(), this->entities.end());

    auto transformed = base_range
        | ranges::views::transform([](const SAPLocation& loc) -> EntityInterface* {
              return loc.referer.get();
          });

    return {transformed};
}

std::list<std::pair<EntityInterface*, EntityInterface*>> SweepAndPrune::get_all_collisions() const
{
    std::list<std::pair<EntityInterface*, EntityInterface*>> active_collisions{};
    std::unordered_set<EntityInterface*> active_entities{};

    for (const auto& entity_bound : this->entities)
    {
        EntityInterface* current = entity_bound.referer.get();

        if (entity_bound.is_begin)
        {
            // Check current against all active entities
            for (auto* other : active_entities)
            {
                ColliderInterface& collider1 = current->get_collider();
                ColliderInterface& collider2 = other->get_collider();

                const BoundingBox bbox1 = collider1.get_bounding_box();

                // Guaranteed to overlap on x-axis by SAP; check y-axis
                if (const BoundingBox bbox2 = collider2.get_bounding_box(); bbox1.max.y < bbox2.min.y || bbox1.min.y > bbox2.max.y)
                    continue;

                // Narrow-phase collision
                if (collider1.is_colliding_with(collider2))
                {
                    active_collisions.emplace_back(current, other);
                }
            }

            // Finally, add current entity to active set
            active_entities.insert(current);
        }
        else
        {
            // Remove from active set when its "end" endpoint is reached
            active_entities.erase(current);
        }
    }

    return active_collisions;
}

size_t SweepAndPrune::get_entity_count() const
{
    return this->entities.size() / 2;
}
