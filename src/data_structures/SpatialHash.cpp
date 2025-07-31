#include <ranges>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view/any_view.hpp>
#include <data_structures/SpatialHash.h>

void SpatialHash::add_collider(EntityInterface& other)
{
    ++entity_count;
    cells[compute_hash(other)].emplace_back(other);
}
void SpatialHash::reserve_slots(const size_t n)
{
    cells.reserve(static_cast<size_t>(n * AVERAGE_AGENT_OVERLAP / TARGET_LOAD_FACTOR));
}
std::vector<EntityInterface&> SpatialHash::get_collisions(const EntityInterface& other) const
{
    const hash_key original_key = compute_hash(other);
    const hash_key potential_keys[9] = {
        original_key,
        hash_key(original_key.x + 1, original_key.y),
        hash_key(original_key.x + 1, original_key.y + 1),
        hash_key(original_key.x, original_key.y + 1),
        hash_key(original_key.x - 1, original_key.y + 1),
        hash_key(original_key.x - 1, original_key.y),
        hash_key(original_key.x - 1, original_key.y - 1),
        hash_key(original_key.x, original_key.y - 1),
        hash_key(original_key.x + 1, original_key.y - 1),
    };

    std::vector<EntityInterface&> active_collisions{};

    for (const hash_key& key : potential_keys)
    {
        if (!cells.contains(key)) continue;
        for (const auto& collider : cells.at(key))
        {
            if (other.get_collider().is_colliding_with(collider)) active_collisions.emplace_back(collider);
        }
    }

    return active_collisions;
}
void SpatialHash::update_structure()
{
    for (auto& [old_key, colliders] : cells)
    {
        for (auto it = colliders.begin(); it != colliders.end(); ++it)
        {
            if (const hash_key curr_key = compute_hash(*it); curr_key != old_key)
            {
                colliders.erase(it);
                cells[curr_key].emplace_back(*it);
            }
        }
    }
}

SpatialHash::hash_key SpatialHash::compute_hash(const EntityInterface& other)
{
    const Point center = other.get_location();
    return hash_key(static_cast<int>(center.x * POSITION_TO_CELL), static_cast<int>(center.y * POSITION_TO_CELL));
}

ranges::any_view<EntityInterface&> SpatialHash::get_all_entities() const
{
    auto range = ranges::make_iterator_range(this->begin(), this->end());
    return ranges::any_view<EntityInterface&>{range};
}

inline size_t SpatialHash::get_entity_count() const
{
    return entity_count;
}


