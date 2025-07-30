#include <data_structures/NaiveLinear.h>

void NaiveLinear::reserve_slots(const size_t n)
{
    this->colliders.reserve(n);
}
void NaiveLinear::add_collider(ColliderInterface& other)
{
    this->colliders.emplace_back(other);
}
void NaiveLinear::update_structure()
{

}
std::vector<ColliderInterface&> NaiveLinear::get_collisions(const ColliderInterface& other) const
{
    std::vector<ColliderInterface&> active_collisions;
    active_collisions.reserve(6);  // just to stop the silly resizing that happens at the beginning often.
    for (const auto& collider : this->colliders)
    {
        if (other.is_colliding_with(collider)) active_collisions.push_back(collider);
    }
    return active_collisions;
}
