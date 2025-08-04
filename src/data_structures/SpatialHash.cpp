#include <range/v3/view/subrange.hpp>
#include <range/v3/view/any_view.hpp>
#include <data_structures/SpatialHash.h>

void SpatialHash::add_collider(EntityInterface& other)
{
    ++entity_count;
    cells[compute_hash(other)].emplace_back(&other);
}
void SpatialHash::reserve_slots(const size_t n)
{
    cells.reserve(static_cast<size_t>(n * AVERAGE_AGENT_OVERLAP / TARGET_LOAD_FACTOR));
}
std::vector<EntityInterface*> SpatialHash::get_collisions(const EntityInterface& other) const
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

    std::vector<EntityInterface*> active_collisions{};

    for (const hash_key& key : potential_keys)
    {
        if (!cells.contains(key)) continue;
        for (auto* entity : cells.at(key))
        {
            if (other.get_collider().is_colliding_with(entity->get_collider())) active_collisions.emplace_back(entity);
        }
    }

    return active_collisions;
}
void SpatialHash::update_structure()
{
    std::unordered_map<hash_key, std::list<EntityInterface*>, hash_key_hasher> new_cells;
    new_cells.reserve(static_cast<size_t>(this->get_entity_count() * AVERAGE_AGENT_OVERLAP / TARGET_LOAD_FACTOR));

    for (auto& [old_key, colliders] : cells)
    {
        for (auto it = colliders.begin(); it != colliders.end(); )
        {
            if (const hash_key curr_key = compute_hash(**it); curr_key != old_key)
            {
                new_cells[curr_key].emplace_back(*it);
                it = colliders.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    for (auto& [k, v] : new_cells)
    {
        cells[k].splice(cells[k].end(), v);
    }

    std::erase_if(cells, [](const auto& pair) { return pair.second.empty(); });
}

SpatialHash::hash_key SpatialHash::compute_hash(const EntityInterface& other)
{
    const Point center = other.get_location();
    return hash_key(static_cast<int>(std::floor(center.x * POSITION_TO_CELL)), static_cast<int>(std::floor(center.y * POSITION_TO_CELL)));
}

ranges::any_view<EntityInterface*> SpatialHash::get_all_entities() const
{
    auto range = ranges::subrange(this->begin(), this->end());
    return ranges::any_view<EntityInterface*>{range};
}

size_t SpatialHash::get_entity_count() const
{
    return entity_count;
}

void SpatialHash::draw_debug(RendererInterface& renderer) const
{
    for (auto& [key, colliders] : cells)
    {
        OopsBoundingBox bbox{key.x * CELL_SIZE, key.y * CELL_SIZE, (key.x + 1) * CELL_SIZE, (key.y + 1) * CELL_SIZE};
        bbox.draw_debug(renderer);

        for (const EntityInterface* entity : colliders)
        {
            entity->get_collider().draw_debug(renderer);
        }
    }
}


