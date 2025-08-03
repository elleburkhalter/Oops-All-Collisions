#ifndef AGENTINTERFACE_H
#define AGENTINTERFACE_H

#include <game_object/interfaces/EntityInterface.h>

class AgentInterface : public EntityInterface
{
public:
    AgentInterface(ColliderInterface& collider, Point pos = {0, 0}, Point vel = {0, 0})
        : EntityInterface(collider), position(pos), velocity(vel) {}
    virtual ~AgentInterface() = default;
        Point get_location() const override { return position; }
    Point get_velocity() const override { return velocity; }

    void set_position(Point pos) override { position = pos; }
    void set_velocity(Point vel) override { velocity = vel; }

    void resolve_collisions() override {
        // Custom logic
    }
    private:
    Point position;
    Point velocity;
    // TODO: Figure out what all an Agent needs to be able to do.
    // I don't know what special methods an Agent might need.

};

#endif //AGENTINTERFACE_H
