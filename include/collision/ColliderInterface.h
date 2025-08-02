#ifndef COLLIDERINTERFACE_H
#define COLLIDERINTERFACE_H

#include <spatial/Point.h>
#include <spatial/OopsBoundingBox.h>
#include <collision/ColliderFlags.h>

class BallCollider;

class ColliderInterface
{
public:
    explicit ColliderInterface(const double mass = 1.0, const double coeff_of_restitution = 1.0): mass(mass), coefficient_of_restitution(coeff_of_restitution) {};
    virtual ~ColliderInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual Point get_centroid() const = 0;
    [[nodiscard]] virtual OopsBoundingBox get_bounding_box() const = 0;

    [[nodiscard]] virtual bool is_colliding_with(const ColliderInterface& other) const = 0;
    [[nodiscard]] virtual CollisionCode resolve_collision_with(ColliderInterface& other) = 0;
    [[nodiscard]] virtual Point compute_impulse_with(ColliderInterface& other) const = 0;
    [[nodiscard]] virtual Point compute_position_correction_with(ColliderInterface& other) const = 0;

    void update(double dt = 0.0);

protected:
    friend class BallCollider;
    [[nodiscard]] virtual bool is_colliding_with_ball(const BallCollider& other) const = 0;
    [[nodiscard]] virtual CollisionCode resolve_collision_with_ball(BallCollider& other) = 0;

    [[nodiscard]] virtual Point compute_impulse_with_ball(const BallCollider& other) const = 0;
    [[nodiscard]] virtual Point compute_position_correction_with_ball(const BallCollider& other) const = 0;

    double mass = 1.0;
    double coefficient_of_restitution = 1.0;

private:
    Point position{};
    Point velocity{};

    Point stored_impulse{};
    Point stored_position_correction{};
};

#endif //COLLIDERINTERFACE_H
