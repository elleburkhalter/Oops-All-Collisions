#ifndef COLLIDERINTERFACE_H
#define COLLIDERINTERFACE_H

#include <spatial/Point.h>
#include <spatial/BoundingBox.h>
#include <collision/ColliderFlags.h>

class BallCollider;

class ColliderInterface
{
public:
    ColliderInterface() = delete;
    virtual ~ColliderInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual Point get_centroid() const = 0;
    [[nodiscard]] virtual BoundingBox get_bounding_box() const = 0;

    [[nodiscard]] virtual CollisionCode resolve_collision_with(ColliderInterface& other) = 0;

protected:
    friend class BallCollider;
    [[nodiscard]] virtual CollisionCode resolve_collision_with_ball(BallCollider& other) = 0;
};

#endif //COLLIDERINTERFACE_H
