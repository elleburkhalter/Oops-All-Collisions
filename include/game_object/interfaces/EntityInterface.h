#ifndef ENTITYINTERFACE_H
#define ENTITYINTERFACE_H

#include <cinttypes>
#include <game_object/interfaces/EntityFlags.h>
#include <collision/ColliderInterface.h>
#include <spatial/Point.h>

class EntityInterface
{
public:
    explicit EntityInterface(ColliderInterface& collider): collider(collider) {};
    virtual ~EntityInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual inline Point get_location() const = 0;  // should be called by renderer to plot point
    [[nodiscard]] virtual inline Point get_velocity() const = 0;
    [[nodiscard]] ColliderInterface& get_collider() const { return collider; }
    template <typename T>
    [[nodiscard]] std::shared_ptr<T> get_tag() { return std::static_pointer_cast<T>(this->tag.lock()); };

    // ----- Setters -----
    void set_movement_enabled() { flags |= EntityFlags::MovementEnabled; }
    void set_movement_disabled() { flags &= ~EntityFlags::MovementEnabled; }
    void set_movement_flag(const bool flag) { flag ? set_movement_enabled() : set_movement_disabled(); }

    void set_collision_enabled() { flags |= EntityFlags::CollisionEnabled; }
    void set_collision_disabled() { flags &= ~EntityFlags::CollisionEnabled; }
    void set_collision_flag(const bool flag) { flag ? set_collision_enabled() : set_collision_disabled(); }

    virtual inline void set_position(Point pos) = 0;
    virtual inline void set_velocity(Point vel) = 0;

    template <typename T>
    void set_tag(const std::shared_ptr<T>& ptr) { tag = std::static_pointer_cast<void>(ptr); };

    // ----- Checkers -----
    [[nodiscard]] bool movement_enabled() const { return flags & EntityFlags::MovementEnabled; }
    [[nodiscard]] bool collision_enabled() const { return flags & EntityFlags::CollisionEnabled; }

    // ----- Frame Updates and Collision Logic -----
    virtual void resolve_collisions() = 0;

private:
    ColliderInterface& collider;
    uint8_t flags = EntityFlags::MovementEnabled | EntityFlags::CollisionEnabled;
    std::weak_ptr<void> tag{};
};

#endif //ENTITYINTERFACE_H
