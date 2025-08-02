#include <cmath>
#include <collision/BallCollider.h>

CollisionCode BallCollider::resolve_collision_with(ColliderInterface& other)
{
    return other.resolve_collision_with_ball(*this);
}
bool BallCollider::is_colliding_with(const ColliderInterface& other) const
{
    return other.is_colliding_with_ball(*this);
}
Point BallCollider::compute_impulse_with(ColliderInterface& other) const
{
    return other.compute_impulse_with_ball(*this);
}
Point BallCollider::compute_position_correction_with(ColliderInterface& other) const
{
    return other.compute_position_correction_with_ball(*this);
}

Point BallCollider::compute_impulse_with_ball(const BallCollider& other) const
{
    const Point relative_velocity = this->velocity - other.velocity;

    Point normal{0.0, 0.0};
    if (this->position != other.position)
    {
        normal = this->position - other.position;
        normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y);
    }

    const double relative_parallel_velocity = normal.x * relative_velocity.x + normal.y * relative_velocity.y;
    if (relative_parallel_velocity >= 0.0) return {0, 0};

    const double inv_mass_a = (this->mass == 0) ? 0 : 1.0 / this->mass;
    const double inv_mass_b = (other.mass == 0) ? 0 : 1.0 / other.mass;

    const double j_mag = -(1.0 + this->coefficient_of_restitution) * relative_parallel_velocity / (inv_mass_a + inv_mass_b);

    return j_mag * normal;
}
Point BallCollider::compute_position_correction_with_ball(const BallCollider& other) const
{
    if (const double penetration = (this->collider_base.radius + other.collider_base.radius) - Point::get_distance(this->get_centroid(), other.get_centroid()); penetration > 0)
    {
        const double inv_mass_a = (this->mass == 0) ? 0 : 1.0 / this->mass;
        const double inv_mass_b = (other.mass == 0) ? 0 : 1.0 / other.mass;

        constexpr double percent = 0.2;
        constexpr double slop = 0.01;

        const double correction_mag = std::max(penetration - slop, 0.0) / (inv_mass_a + inv_mass_b) * percent;
        Point normal{1.0, 0};
        if (this->position != other.position)
        {
            normal = this->position - other.position;
            normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y);
        }
        return correction_mag * normal;
    }
    return {0, 0};
}

CollisionCode BallCollider::resolve_collision_with_ball(BallCollider& other)
{
    if (is_colliding_with_ball(other))
    {
        const Point impulse = compute_impulse_with_ball(other);
        const Point position_correction = compute_position_correction_with_ball(other);

        this->position += position_correction;
        this->velocity += impulse / mass;

        other.position -= position_correction;
        other.velocity -= impulse / mass;

        return CollisionCode::COLLISION_PRESENT;
    }
    return CollisionCode::COLLISION_ABSENT;
}
bool BallCollider::is_colliding_with_ball(const BallCollider& other) const
{
    const double combined_rad = other.collider_base.radius + this->collider_base.radius;
    return Point::get_distance_sq(other.collider_base.center, this->collider_base.center) < combined_rad * combined_rad;
}

OopsBoundingBox BallCollider::get_bounding_box() const
{
    return {
        this->collider_base.center.x - this->collider_base.radius,
        this->collider_base.center.y - this->collider_base.radius,
        this->collider_base.center.x + this->collider_base.radius,
        this->collider_base.center.y + this->collider_base.radius
    };
}



