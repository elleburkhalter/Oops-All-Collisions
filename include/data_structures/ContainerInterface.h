#ifndef CONTAINERINTERFACE_H
#define CONTAINERINTERFACE_H

#include <vector>
#include <game_object/interfaces/EntityInterface.h>

class ContainerInterface
{
public:
    ContainerInterface() = default;
    virtual ~ContainerInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual std::vector<EntityInterface&> get_collisions(const EntityInterface& other) const = 0;

    // ----- Initialization -----
    virtual void reserve_slots(size_t n) = 0;
    virtual void add_collider(EntityInterface& other) = 0;
    virtual void update_structure() = 0;  // should be called after moving entities and changing positions/bounding boxes
};

#endif //CONTAINERINTERFACE_H
