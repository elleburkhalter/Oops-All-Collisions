#include <collision/ColliderInterface.h>

void ColliderInterface::update(const double dt)
{
    this->set_position(this->get_centroid() + stored_position_correction);
    this->velocity += stored_impulse / mass;

    this->set_position(this->get_centroid() + this->velocity * dt);
}