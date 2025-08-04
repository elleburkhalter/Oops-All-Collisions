#ifndef BASICENEMY_H
#define BASICENEMY_H

#include <collision/BallCollider.h>
#include <game_object/interfaces/EntityInterface.h>
#include <game_object/interfaces/AgentInterface.h>

class BasicEnemy final : public EntityInterface, public AgentInterface
{
public:
    BasicEnemy(const double x, const double y, const double vx = 0.0, const double vy = 0.0): EntityInterface(collider), collider{Ball{x, y, 1.0}} { collider.set_velocity({vx, vy}); };

    [[nodiscard]] Point get_location() const override { return collider.get_centroid(); }
    [[nodiscard]] Point get_velocity() const override { return collider.get_velocity(); }
    [[nodiscard]] ColliderInterface& get_collider() { return collider; }

    void draw(RendererInterface& renderer) const override {renderer.draw_point(get_location()); renderer.draw_circle(collider.get_underlying_ball()); };

private:
    BallCollider collider;
};

#endif //BASICENEMY_H
