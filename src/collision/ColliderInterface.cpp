#include <collision/ColliderInterface.h>

void ColliderInterface::update(const double dt)
{
    this->set_position(this->get_centroid() + stored_position_correction);
    this->velocity += stored_impulse / mass;

    stored_position_correction = {0, 0};
    stored_impulse = {0, 0};

    this->set_position(this->get_centroid() + this->velocity * dt);
}