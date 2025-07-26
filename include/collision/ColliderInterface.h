#ifndef COLLIDERINTERFACE_H
#define COLLIDERINTERFACE_H

#include <spatial/Point.h>
#include <collision/ColliderFlags.h>

class BallCollider;

class ColliderInterface
{
public:
    explicit ColliderInterface(const bool movable): movable(movable) {};
    virtual ~ColliderInterface() = default;
    [[nodiscard]] virtual CollisionCode resolve_collision_with(ColliderInterface& other) = 0;

    [[nodiscard]] virtual Point get_centroid() const = 0;
    [[nodiscard]] bool is_movable() const { return movable; };

protected:
    friend class BallCollider;
    [[nodiscard]] virtual CollisionCode resolve_collision_with_ball(BallCollider& other) = 0;

    bool movable = true;
};

#endif //COLLIDERINTERFACE_H
