#include <collision/BallCollider.h>

inline CollisionCode BallCollider::resolve_collision_with(ColliderInterface& other)
{
    return other.resolve_collision_with_ball(*this);
}
CollisionCode BallCollider::resolve_collision_with_ball(BallCollider& other)
{
    // TODO: Decide whether to use constraints or iterative solver.
    return CollisionCode::COLLISION_ABSENT;
}

