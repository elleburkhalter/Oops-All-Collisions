#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include <unordered_map>
#include <data_structures/ContainerInterface.h>

class SpatialHash final : public ContainerInterface
{
public:
    SpatialHash() = default;

    [[nodiscard]] std::vector<ColliderInterface&> get_collisions(const ColliderInterface& other) const override;

    void reserve_slots(size_t n) override;
    void add_collider(ColliderInterface& other) override;
    void update_structure() override;

    static constexpr double TARGET_LOAD_FACTOR = 0.7;
    static constexpr double AVERAGE_AGENT_OVERLAP = 1.5;
    static constexpr double CELL_SIZE = 16.0;

private:

    static constexpr double POSITION_TO_CELL = 1.0 / CELL_SIZE;

    struct hash_key {
        int x, y;
        explicit hash_key(const int x = 0, const int y = 0): x(x), y(y) {}
        bool operator==(const hash_key& other) const { return x == other.x && y == other.y; }
    };

    struct hash_key_hasher {
        std::size_t operator()(const hash_key& key) const { return std::hash<int>()(key.x) ^ (std::hash<int>()(key.y) << 1); }
    };

    std::unordered_map<hash_key, std::list<ColliderInterface&>, hash_key_hasher> cells;
    [[nodiscard]] static hash_key compute_hash(const ColliderInterface& other) ;
};

#endif //SPATIALHASH_H
