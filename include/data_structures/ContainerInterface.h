#ifndef CONTAINERINTERFACE_H
#define CONTAINERINTERFACE_H

#include <stdexcept>
#include <vector>
#include <range/v3/view/any_view.hpp>
#include <game_object/interfaces/EntityInterface.h>

class ContainerInterface
{
public:
    ContainerInterface() = default;
    virtual ~ContainerInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual std::vector<EntityInterface&> get_collisions(const EntityInterface& other) const { throw std::exception{"Container implementation does not support single-collision lookups."}; };
    [[nodiscard]] virtual std::vector<std::pair<EntityInterface&, EntityInterface&>> get_all_collisions() const;
    [[nodiscard]] virtual ranges::any_view<EntityInterface&> get_all_entities() const = 0;

    // ----- Initialization -----
    virtual void reserve_slots(size_t n) = 0;
    virtual void add_collider(EntityInterface& other) = 0;
    virtual void update_structure() = 0;  // should be called after moving entities and changing positions/bounding boxes
};

#endif //CONTAINERINTERFACE_H
