#ifndef BALLCOLLIDER_H
#define BALLCOLLIDER_H

#include <collision/ColliderInterface.h>
#include <spatial/Ball.h>

#include <utility>

class BallCollider final : public ColliderInterface
{
public:
    explicit BallCollider(Ball other, const bool movable = true): ColliderInterface(movable), collider_base(std::move(other)) {};

    [[nodiscard]] Point get_centroid() const override { return collider_base.get_centroid(); };
    [[nodiscard]] inline CollisionCode resolve_collision_with(ColliderInterface& other) override;

protected:
    [[nodiscard]] CollisionCode resolve_collision_with_ball(BallCollider& other) override;

private:

    Ball collider_base;
};

#endif //BALLCOLLIDER_H
