#include <unordered_set>
#include <data_structures/ContainerInterface.h>

std::list<std::pair<EntityInterface*, EntityInterface*>> ContainerInterface::get_all_collisions() const
{
    std::list<std::pair<EntityInterface*, EntityInterface*>> active_collisions;
    const auto table_size = static_cast<size_t>(static_cast<double>(this->get_entity_count()) * AVERAGE_COLLISIONS_PER_ENTITY / TARGET_LOAD_FACTOR);
    std::unordered_set<collision_record, collision_record_hasher> visited_collisions{};
    visited_collisions.reserve(table_size);

    for (EntityInterface* entity1 : this->get_all_entities())
    {
        for (EntityInterface* entity2 : this->get_collisions(*entity1))
        {
            if (entity1 == entity2) continue;  // check for self-collision.

            if (const collision_record collision(entity2, entity1); visited_collisions.contains(collision)) continue;
            visited_collisions.emplace(entity1, entity2);
            active_collisions.emplace_back(entity1, entity2);
        }
    }
    return active_collisions;
}
