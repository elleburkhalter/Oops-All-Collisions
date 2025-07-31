#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include <range/v3/view/any_view.hpp>
#include <unordered_map>
#include <data_structures/ContainerInterface.h>

class SpatialHash final : public ContainerInterface
{
    class iterator;
public:
    SpatialHash() = default;

    // ----- Getters -----
    [[nodiscard]] std::vector<EntityInterface*> get_collisions(const EntityInterface& other) const override;
    [[nodiscard]] ranges::any_view<EntityInterface*> get_all_entities() const override;
    [[nodiscard]] inline size_t get_entity_count() const override;

    // ----- Initialization -----
    void reserve_slots(size_t n) override;
    void add_collider(EntityInterface& other) override;
    void update_structure() override;

    [[nodiscard]] iterator begin() const { return {cells.begin(), cells.end()}; }
    [[nodiscard]] iterator end() const { return {cells.end(), cells.end()}; }

    static constexpr double TARGET_LOAD_FACTOR = 0.7;
    static constexpr double AVERAGE_AGENT_OVERLAP = 1.5;
    static constexpr double CELL_SIZE = 16.0;

private:

    struct hash_key;
    struct hash_key_hasher;

    static constexpr double POSITION_TO_CELL = 1.0 / CELL_SIZE;
    std::unordered_map<hash_key, std::list<EntityInterface*>, hash_key_hasher> cells;
    [[nodiscard]] static hash_key compute_hash(const EntityInterface& other);
    size_t entity_count = 0;

    struct hash_key {
        int x, y;
        explicit hash_key(const int x = 0, const int y = 0): x(x), y(y) {}
        bool operator==(const hash_key& other) const { return x == other.x && y == other.y; }
    };

    struct hash_key_hasher {
        std::size_t operator()(const hash_key& key) const { return std::hash<int>()(key.x) ^ (std::hash<int>()(key.y) << 1); }
    };

    class iterator
    {
    public:
        using _outer_iter = std::unordered_map<
            hash_key, std::list<EntityInterface*>, hash_key_hasher>::const_iterator;
        using _inner_iter = std::list<EntityInterface*>::const_iterator;

        using iterator_category = std::forward_iterator_tag;
        using value_type = EntityInterface*;      // what is stored in the container
        using reference = EntityInterface*;       // what operator* returns
        using pointer = EntityInterface**;        // operator-> returns a pointer-to-pointer
        using difference_type = std::ptrdiff_t;

        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        iterator(iterator&&) noexcept = default;
        iterator& operator=(iterator&&) noexcept = default;
        ~iterator() noexcept = default;

        iterator(const _outer_iter outer, const _outer_iter outer_end)
            : outer(outer), outer_end(outer_end)
        {
            if (outer != outer_end) {
                inner = outer->second.begin();
                skip_empty();
            }
        }

        // Now just return the pointer itself
        reference operator*() const { return *inner; }

        // For operator->, return address of the pointer in the list
        pointer operator->() const { return const_cast<pointer>(&(*inner)); }

        iterator& operator++()
        {
            ++inner;
            skip_empty();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return outer == other.outer && (outer == outer_end || inner == other.inner);
        }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        void skip_empty()
        {
            while (outer != outer_end && inner == outer->second.end())
            {
                ++outer;
                if (outer != outer_end)
                    inner = outer->second.begin();
            }
        }

        _outer_iter outer{};
        _outer_iter outer_end{};
        _inner_iter inner{};
    };
};

#endif //SPATIALHASH_H
