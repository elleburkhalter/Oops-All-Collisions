#include <collision/BallCollider.h>

inline CollisionCode BallCollider::resolve_collision_with(ColliderInterface& other)
{
    return other.resolve_collision_with_ball(*this);
}
bool BallCollider::is_colliding_with(const ColliderInterface& other) const
{
    return other.is_colliding_with_ball(*this);
}

CollisionCode BallCollider::resolve_collision_with_ball(BallCollider& other)
{
    // TODO: Decide whether to use constraints or iterative solver.
    return CollisionCode::COLLISION_ABSENT;
}
bool BallCollider::is_colliding_with_ball(const BallCollider& other) const
{
    const double combined_rad = other.collider_base.radius + this->collider_base.radius;
    return Point::get_distance_sq(other.collider_base.center, this->collider_base.center) < combined_rad * combined_rad;
}


