#ifndef BALLCOLLIDER_H
#define BALLCOLLIDER_H

#include <collision/ColliderInterface.h>
#include <spatial/Ball.h>

#include <utility>

class BallCollider final : public ColliderInterface
{
public:

    explicit BallCollider(Ball other): collider_base(std::move(other)) {};

    [[nodiscard]] Point get_centroid() const override { return collider_base.get_centroid(); };
    [[nodiscard]] BoundingBox get_bounding_box() const override;

    [[nodiscard]] inline CollisionCode resolve_collision_with(ColliderInterface& other) override;
    [[nodiscard]] inline bool is_colliding_with(const ColliderInterface& other) const override;
    [[nodiscard]] inline Point compute_position_correction_with(ColliderInterface& other) const override;
    [[nodiscard]] inline Point compute_impulse_with(ColliderInterface& other) const override;

protected:
    [[nodiscard]] CollisionCode resolve_collision_with_ball(BallCollider& other) override;
    [[nodiscard]] inline bool is_colliding_with_ball(const BallCollider& other) const override;
    [[nodiscard]] inline Point compute_impulse_with_ball(const BallCollider& other) const override;
    [[nodiscard]] inline Point compute_position_correction_with_ball(const BallCollider& other) const override;

private:
    Ball collider_base;
};

#endif //BALLCOLLIDER_H
