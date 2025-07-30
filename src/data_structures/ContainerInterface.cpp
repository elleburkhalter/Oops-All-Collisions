#include <data_structures/ContainerInterface.h>

std::vector<std::pair<EntityInterface&, EntityInterface&>> ContainerInterface::get_all_collisions() const
{
    std::vector<std::pair<EntityInterface&, EntityInterface&>> active_collisions;
    for (EntityInterface& entity1 : this->get_all_entities())
    {
        for (EntityInterface& entity2 : this->get_collisions(entity1))
        {
            if (&entity1 == &entity2) continue;  // check for self-collision.
            active_collisions.emplace_back(entity1, entity2);
        }
    }
    return active_collisions;
}
