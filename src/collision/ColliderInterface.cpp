#include <collision/ColliderInterface.h>

void ColliderInterface::update(const double dt)
{
    this->position += stored_position_correction;
    this->velocity += stored_impulse / mass;

    this->position += this->velocity * dt;
}