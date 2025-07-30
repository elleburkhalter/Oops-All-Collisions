#ifndef ENTITYINTERFACE_H
#define ENTITYINTERFACE_H

#include <cinttypes>
#include <game_object/base/EntityFlags.h>
#include <collision/ColliderInterface.h>
#include <spatial/Point.h>

class EntityInterface
{
public:
    EntityInterface() = delete;
    virtual ~EntityInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual inline Point get_location() const = 0;  // should be called by renderer to plot point
    [[nodiscard]] virtual inline Point get_velocity() const = 0;

    // ----- Checkers -----
    [[nodiscard]] bool movement_enabled() const  { return flags & EntityFlags::MovementEnabled; }
    [[nodiscard]] bool collision_enabled() const { return flags & EntityFlags::CollisionEnabled; }

    // ----- Frame Updates and Collision Logic ? -----
    virtual void move(double dt) = 0;  // perform wander
    virtual void resolve_collisions() = 0;

protected:
    ColliderInterface& collider;
    uint8_t flags;
};

#endif //ENTITYINTERFACE_H
