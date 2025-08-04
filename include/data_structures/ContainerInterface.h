#ifndef CONTAINERINTERFACE_H
#define CONTAINERINTERFACE_H

#include <stdexcept>
#include <vector>
#include <list>
#include <range/v3/view/any_view.hpp>
#include <game_object/interfaces/EntityInterface.h>

#include <game_object/enemies/BasicEnemy.h>
#include <random/NormalDistribution.h>
#include <constants.h>
#include <range/v3/action/concepts.hpp>

class ContainerInterface : public DebugDrawableInterface
{
public:
    ContainerInterface() = default;
    ~ContainerInterface() override
    {
        for (const EntityInterface* entity : this->entities) delete entity;
    }
    // This is SOOO cursed; I don't have big five; don't worry about it.

    // ----- Getters -----
    [[nodiscard]] virtual std::vector<EntityInterface*> get_collisions(const EntityInterface& other) const { throw std::runtime_error{"Container implementation does not support single-collision lookups."}; }
    [[nodiscard]] virtual std::list<std::pair<EntityInterface*, EntityInterface*>> get_all_collisions() const;
    [[nodiscard]] virtual ranges::any_view<EntityInterface*> get_all_entities() const = 0;
    [[nodiscard]] virtual size_t get_entity_count() const = 0;

    // ----- Initialization -----
    virtual void reserve_slots(size_t n) = 0;
    virtual void add_collider(EntityInterface& other) = 0;
    void add_basic_enemy()
    {
        EntityInterface* entity = new BasicEnemy(POS_SPREAD * NormalDistribution::poll(), POS_SPREAD * NormalDistribution::poll(), VEL_SPREAD * NormalDistribution::poll(), VEL_SPREAD * NormalDistribution::poll());
        entities.push_back(entity);
        add_collider(*entity);
    };
    virtual void post_bulk_add_callback() {};
    virtual void update_structure() = 0;  // should be called after moving entities and changing positions/bounding boxes

    // For default implementation of get_all_collisions();
    static constexpr double TARGET_LOAD_FACTOR = COLLISION_RECORD_TARGET_LOAD_FACTOR;
    static constexpr double AVERAGE_COLLISIONS_PER_ENTITY = ESTIMATED_AVERAGE_COLLISIONS_PER_ENTITY;

private:
    std::list<EntityInterface*> entities;

    struct collision_record
    {
        EntityInterface* entity_1;
        EntityInterface* entity_2;
        explicit collision_record(EntityInterface* entity_1 = nullptr, EntityInterface* entity_2 = nullptr): entity_1(entity_1), entity_2(entity_2) {};
        bool operator==(const collision_record& other) const { return (entity_1 == other.entity_1 && entity_2 == other.entity_2) || (entity_1 == other.entity_2 && entity_2 == other.entity_1); }
    };

    struct collision_record_hasher
    {
        std::size_t operator()(const collision_record& key) const { return std::hash<EntityInterface*>()(key.entity_1) ^ std::hash<EntityInterface*>()(key.entity_2); }
    };
};

#endif //CONTAINERINTERFACE_H
