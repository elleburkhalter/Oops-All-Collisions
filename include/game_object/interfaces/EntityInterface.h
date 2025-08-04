#ifndef ENTITYINTERFACE_H
#define ENTITYINTERFACE_H

#include <cinttypes>
#include <memory>
#include <game_object/interfaces/EntityFlags.h>
#include <collision/ColliderInterface.h>
#include <spatial/Point.h>

class RendererInterface;

class EntityInterface
{
public:
    explicit EntityInterface(ColliderInterface& collider): collider(collider) {};
    virtual ~EntityInterface() = default;

    // ----- Getters -----
    [[nodiscard]] virtual Point get_location() const = 0;  // should be called by renderer to plot point
    [[nodiscard]] virtual Point get_velocity() const = 0;
    [[nodiscard]] ColliderInterface& get_collider() const { return collider; }
    template <typename T>
    [[nodiscard]] std::shared_ptr<T> get_tag() { return std::static_pointer_cast<T>(this->tag.lock()); };

    // ----- Setters -----
    void set_movement_enabled() { collider.set_mass(saved_mass); flags |= EntityFlags::MovementEnabled; }
    void set_movement_disabled() { saved_mass = collider.get_mass(); collider.set_mass(0.0); flags &= ~EntityFlags::MovementEnabled; }
    void set_movement_flag(const bool flag) { flag ? set_movement_enabled() : set_movement_disabled(); }

    void set_collision_enabled() { flags |= EntityFlags::CollisionEnabled; }
    void set_collision_disabled() { flags &= ~EntityFlags::CollisionEnabled; }
    void set_collision_flag(const bool flag) { flag ? set_collision_enabled() : set_collision_disabled(); }

    virtual void set_position(const Point pos) { this->collider.set_position(pos); };
    virtual void set_velocity(const Point vel) { this->collider.set_velocity(vel); };

    template <typename T>
    void set_tag(const std::shared_ptr<T>& ptr) { tag = std::static_pointer_cast<void>(ptr); };

    // ----- Checkers -----
    [[nodiscard]] bool movement_enabled() const { return flags & EntityFlags::MovementEnabled; }
    [[nodiscard]] bool collision_enabled() const { return flags & EntityFlags::CollisionEnabled; }

    // ----- Frame Updates and Collision Logic -----
    virtual void update(const double dt) { this->collider.update(dt); };
    virtual void draw(RendererInterface& renderer) const = 0;

private:
    double saved_mass = 0.0;
    ColliderInterface& collider;
    std::uint8_t flags = EntityFlags::MovementEnabled | EntityFlags::CollisionEnabled;
    std::weak_ptr<void> tag{};
};

#endif //ENTITYINTERFACE_H
