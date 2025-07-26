#ifndef ENTITYABC_H
#define ENTITYABC_H

#include <collision/ColliderInterface.h>
#include <collision/ColliderFlags.h>

class EntityABC
{
public:
    explicit EntityABC(ColliderInterface& collider): collider(collider) {}
    virtual ~EntityABC() = default;

    virtual CollisionCode resolve_collision_with(EntityABC& other) = 0;
    [[nodiscard]] Point get_centroid() const { return collider.get_centroid(); };
    virtual void move(double dt) = 0;

private:
    ColliderInterface& collider;
};

#endif //ENTITYABC_H
