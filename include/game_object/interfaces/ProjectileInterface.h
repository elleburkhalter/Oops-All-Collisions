#ifndef PROJECTILEINTERFACE_H
#define PROJECTILEINTERFACE_H
#include <game_object/interfaces/EntityInterface.h>

class ProjectileInterface : EntityInterface
{
public:
    ProjectileInterface() = default;
    virtual ~ProjectileInterface()() = default;

    // TODO: Figure out what all a Projectile needs to be able to do.
    // I don't know what special methods a Projectile might need.

};

#endif //PROJECTILEINTERFACE_H
