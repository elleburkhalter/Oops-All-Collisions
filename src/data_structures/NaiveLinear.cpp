#include <range/v3/view/subrange.hpp>
#include <data_structures/NaiveLinear.h>

void NaiveLinear::reserve_slots(const size_t n)
{
    this->entities.reserve(n);
}
void NaiveLinear::add_collider(EntityInterface& other)
{
    this->entities.emplace_back(&other);
}
void NaiveLinear::update_structure()
{

}
std::vector<EntityInterface*> NaiveLinear::get_collisions(const EntityInterface& other) const
{
    std::vector<EntityInterface*> active_collisions;
    active_collisions.reserve(6);  // just to stop the silly resizing that happens at the beginning often.
    for (EntityInterface* entity : this->entities)
    {
        if (other.get_collider().is_colliding_with(entity->get_collider())) active_collisions.emplace_back(entity);
    }
    return active_collisions;
}
ranges::any_view<EntityInterface*> NaiveLinear::get_all_entities() const
{
    return ranges::subrange(this->entities.begin(), this->entities.end());
}

size_t NaiveLinear::get_entity_count() const
{
    return this->entities.size();
}
