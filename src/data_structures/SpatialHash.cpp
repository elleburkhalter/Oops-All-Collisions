#include <data_structures/SpatialHash.h>

void SpatialHash::add_collider(ColliderInterface& other)
{
    cells[compute_hash(other)].emplace_back(other);
}
void SpatialHash::reserve_slots(const size_t n)
{
    cells.reserve(static_cast<size_t>(n * AVERAGE_AGENT_OVERLAP / TARGET_LOAD_FACTOR));
}
std::vector<ColliderInterface&> SpatialHash::get_collisions(const ColliderInterface& other) const
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

    std::vector<ColliderInterface&> active_collisions{};

    for (const hash_key& key : potential_keys)
    {
        if (!cells.contains(key)) continue;
        for (const auto& collider : cells.at(key))
        {
            if (other.is_colliding_with(collider)) active_collisions.emplace_back(collider);
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



