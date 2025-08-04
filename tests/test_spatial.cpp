#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <collision/BallCollider.h>
#include <spatial/Ball.h>
#include <data_structures/MultiLevelGrid.h>
#include <data_structures/NaiveLinear.h>
#include <data_structures/SpatialHash.h>
#include <data_structures/SweepAndPrune.h>

using Catch::Matchers::WithinAbs;
//All test cases assume perfectly elastic

TEST_CASE("Collision conserves momentum and updates velocities correctly", "[ball_to_ball][velocity][momentum]") {
    Ball ballA({9.6, 8.0}, 7.0);
    Ball ballB({1.5, 8.7}, 2.5);

    BallCollider colliderA(ballA);
    BallCollider colliderB(ballB);

    colliderA.set_mass(5.5);
    colliderB.set_mass(2.6);

    colliderA.set_velocity({3.0, 0.0});
    colliderB.set_velocity({1.1, 3.3});

    //Initial total momentum
    Point initial_momentum = colliderA.get_momentum() + colliderB.get_momentum();

    // Resolve collision
    CollisionCode code = colliderA.resolve_collision_with(colliderB);
    CHECK(code == CollisionCode::COLLISION_PRESENT);

    //Total momentum after collision
    Point final_momentum = colliderA.get_momentum() + colliderB.get_momentum();

    //Total momentum conserved
    CHECK(final_momentum.x == initial_momentum.x);
    CHECK(final_momentum.y == initial_momentum.y);

    //Correct final velocities
    CHECK_THAT(colliderA.get_velocity().x, WithinAbs(1.78, 0.01));
    CHECK_THAT(colliderB.get_velocity().x, WithinAbs(3.68, 0.01));
    CHECK_THAT(colliderA.get_velocity().y, WithinAbs(2.12, 0.01));
    CHECK_THAT(colliderB.get_velocity().y, WithinAbs(-1.18, 0.01));

    //Positions should move apart at least sum of radii
    double dist_after = Point::get_distance(colliderA.get_centroid(), colliderB.get_centroid());
    CHECK(dist_after >= ballA.radius + ballB.radius);
}

TEST_CASE("Collision updates velocities correctly", "[ball_to_ball][velocity]") {
    Ball ballA({14.6, 34.3}, 1.2);
    Ball ballB({15.2, 33.4}, 1.3);

    BallCollider colliderA(ballA);
    BallCollider colliderB(ballB);

    colliderA.set_mass(0.6);
    colliderB.set_mass(2.5);

    colliderA.set_velocity({10.6, 5.3});
    colliderB.set_velocity({2.2, 3.2});

    CollisionCode code = colliderA.resolve_collision_with(colliderB);
    CHECK(code == CollisionCode::COLLISION_PRESENT);

    //Correct final velocities
    CHECK_THAT(colliderA.get_velocity().x, WithinAbs(-2.95, 0.01));
    CHECK_THAT(colliderB.get_velocity().x, WithinAbs(5.45, 0.01));
    CHECK_THAT(colliderA.get_velocity().y, WithinAbs(1.91, 0.01));
    CHECK_THAT(colliderB.get_velocity().y, WithinAbs(4.01, 0.01));
}

TEST_CASE("Negative velocity test case", "[ball_to_ball][velocity]") {
    Ball ballA({32.2, 90.9}, 57.5);
    Ball ballB({43.5, 100.1}, 10.0);

    BallCollider colliderA(ballA);
    BallCollider colliderB(ballB);

    colliderA.set_mass(13.6);
    colliderB.set_mass(6.6);

    colliderA.set_velocity({-3.3, -4.6});
    colliderB.set_velocity({2.1, 5.0});

    CollisionCode code = colliderA.resolve_collision_with(colliderB);
    CHECK(code == CollisionCode::COLLISION_PRESENT);

    CHECK_THAT(colliderA.get_velocity().x, WithinAbs(0.23, 0.01));
    CHECK_THAT(colliderB.get_velocity().x, WithinAbs(-5.17, 0.01));
    CHECK_THAT(colliderA.get_velocity().y, WithinAbs(1.67, 0.01));
    CHECK_THAT(colliderB.get_velocity().y, WithinAbs(-7.93, 0.01));
}

TEST_CASE("Ball changes X velocity after colliding with bounding box", "[ball_to_bounding_box][velocity]") {
    Ball ball({4.9, 5.0}, 1.0);  //Radius overlaps left wall
    BallCollider collider(ball);
    collider.set_mass(1.0);
    collider.set_velocity({-2.0, 1.1});  //Moving left

    OopsBoundingBox box({5.0, 0.0}, {15.0, 10.0});  //Box starts at x = 5.0

    // Check if ball is overlapping the left side of the box
    OopsBoundingBox ballBox = collider.get_bounding_box();
    bool overlapsLeft = ballBox.min.x < box.min.x && ballBox.max.x > box.min.x;

    if (overlapsLeft) {
        //Reverse x-velocity
        Point vel = collider.get_velocity();
        collider.set_velocity({-vel.x, vel.y});
    }

    CHECK_THAT(collider.get_velocity().x, WithinAbs(2.0, 0.01));
    CHECK_THAT(collider.get_velocity().y, WithinAbs(0.0, 0.01));
}

TEST_CASE("Ball changes Y velocity after colliding with bounding box", "[ball_to_bounding_box][velocity]") {
    Ball ball({10.0, 6.9}, 1.0);
    BallCollider collider(ball);
    collider.set_mass(1.0);
    collider.set_velocity({0.0, -4.0});

    OopsBoundingBox box({5.0, 7.0}, {15.0, 20.0});

    OopsBoundingBox ballBox = collider.get_bounding_box();

    //Check if the ball overlaps the wall
    bool overlapsTop = ballBox.min.y < box.min.y && ballBox.max.y > box.min.y;

    if (overlapsTop) {
        Point vel = collider.get_velocity();
        collider.set_velocity({vel.x, -vel.y});
    }

    CHECK_THAT(collider.get_velocity().x, WithinAbs(0.0, 0.01));
    CHECK_THAT(collider.get_velocity().y, WithinAbs(4.0, 0.01));
}

/*
TEST_CASE("MultiLevelGrid returns correct collision pairs", "[MultiLevelGrid]") {
    MultiLevelGrid grid;

    BallCollider colliderA(Ball({9.9, 9.9}, 11.3));
    TestEntity entityA(colliderA);
    entityA.set_position({9.9, 9.9});
    entityA.set_velocity({12.2, 0.3});

    BallCollider colliderB(Ball({8.2, 10.0}, 0.7));  //Collides with entityA
    AgentInterface entityB(colliderB);
    entityB.set_position({8.2, 10.0});
    entityB.set_velocity({3.3, 0.0});

    BallCollider colliderC(Ball({101.4, 43.8}, 13.5));  //No collision
    AgentInterface entityC(colliderC);
    entityC.set_position({101.4, 43.8});
    entityC.set_velocity({1.1, -1.1});

    grid.add_collider(entityA);
    grid.add_collider(entityB);
    grid.add_collider(entityC);

    auto collisions = grid.get_all_collisions();

    REQUIRE(collisions.size() == 1);
    auto [e1, e2] = collisions.front();
    CHECK((e1 == &entityA && e2 == &entityB) || (e1 == &entityB && e2 == &entityA));
}

TEST_CASE("Update_structure correctly rebinds to detect new collisions", "[MultiLevelGrid]") {
    MultiLevelGrid grid;

    BallCollider colliderA(Ball({212.8, 312.8}, 4.3));
    AgentInterface entityA(colliderA);
    entityA.set_position({212.8, 312.8});

    BallCollider colliderB(Ball({14.4, 156.0}, 5.4));
    AgentInterface entityB(colliderB);
    entityB.set_position({14.4, 156.0});

    grid.add_collider(entityA);
    grid.add_collider(entityB);

    //Move entityA into entityB
    entityA.set_position({14.1, 156.1});
    grid.update_structure();

    auto collisions = grid.get_all_collisions();
    CHECK(collisions.size() == 1);
}

TEST_CASE("MultiLevelGrid with no collisions", "[MultiLevelGrid]") {
    MultiLevelGrid grid;

    BallCollider colliderA(Ball({111.1, 9.9}, 17.3));
    AgentInterface entityA(colliderA);
    entityA.set_position({111.1, 9.9});

    BallCollider colliderB(Ball({200.3, 204.0}, 12.5));
    AgentInterface entityB(colliderB);
    entityB.set_position({200.3, 204.0});

    grid.add_collider(entityA);
    grid.add_collider(entityB);

    auto collisions = grid.get_all_collisions();
    CHECK(collisions.empty());
}

TEST_CASE("MultiLevelGrid detects collisions between ball objects", "[MultiLevelGrid][ball_to_ball]") {
    MultiLevelGrid grid;

    Ball ball1({3.2, 6.1}, 2.0);
    Ball ball2({4.7, 6.1}, 1.0);
    Ball ball3({20.1, 22.9}, 3.0); //No collision

    BallCollider collider1(ball1);
    BallCollider collider2(ball2);
    BallCollider collider3(ball3);

    Entity entity1(collider1);
    Entity entity2(collider2);
    Entity entity3(collider3);

    grid.add_collider(entity1);
    grid.add_collider(entity2);
    grid.add_collider(entity3);

    auto collisions = grid.get_collisions(entity1);

    //Should detect entity2 as collision and NOT entity3
    CHECK(std::find(collisions.begin(), collisions.end(), &entity2) != collisions.end());
    CHECK(std::find(collisions.begin(), collisions.end(), &entity3) == collisions.end());

    //Collisions for entity3 should be empty
    auto collisions_for_3 = grid.get_collisions(entity3);
    CHECK(collisions_for_3.empty());
}

TEST_CASE("NaiveLinear adds and counts entities correctly", "[NaiveLinear]") {
    NaiveLinear grid;
    BallCollider colliderA(Ball({90.1, 20.2}, 14.3));
    Entity entityA(colliderA, {0, 0}, {0, 0});

    BallCollider colliderB(Ball({102.4, 86.6}, 1.1));
    Entity entityB(colliderB, {102.4, 86.6}, {0, 0});

    grid.reserve_slots(2);
    grid.add_collider(entityA);
    grid.add_collider(entityB);

    CHECK(grid.get_entity_count() == 2);
}

TEST_CASE("NaiveLinear detects collisions correctly", "[NaiveLinear]") {
    NaiveLinear grid;

    BallCollider colliderA(Ball({9.9, 9.8}, 5.4));
    Entity entityA(colliderA, {9.9, 9.8}, {-1.7, 7.0});

    BallCollider colliderB(Ball({9.0, 7.8}, 2.0)); //Collides with A
    Entity entityB(colliderB, {9.0, 7.8}, {9.0, 4.5});

    BallCollider colliderC(Ball({87.0, 86.7}, 2.0)); //No collision
    Entity entityC(colliderC, {87.0, 86.7}, {-9.0, 2.3});

    grid.add_collider(entityA);
    grid.add_collider(entityB);
    grid.add_collider(entityC);

    auto collisions = grid.get_collisions(entityA);
    REQUIRE(collisions.size() == 1);
    CHECK(collisions[0] == &entityB);
}

TEST_CASE("NaiveLinear returns correct all_entities view", "[NaiveLinear]") {
    NaiveLinear grid;

    BallCollider colliderA(Ball({33, 71}, 1.3));
    Entity entityA(colliderA, {33, 71}, {-0.9, -10});

    BallCollider colliderB(Ball({2, 2}, 1.4));
    Entity entityB(colliderB, {2, 2}, {21.3, 3.0});

    grid.add_collider(entityA);
    grid.add_collider(entityB);

    auto view = grid.get_all_entities();
    std::vector<EntityInterface*> collected;
    for (EntityInterface* e : view) {
        collected.push_back(e);
    }

    REQUIRE(collected.size() == 2);
    CHECK((collected[0] == &entityA || collected[1] == &entityA));
    CHECK((collected[0] == &entityB || collected[1] == &entityB));
}

TEST_CASE("SpatialHash adds entities and counts correctly", "[SpatialHash]") {
    SpatialHash hash;
    BallCollider colliderA(Ball({15.5, 0.4}, 8.6));
    Entity entityA(colliderA, {15.5, 0.4}, {3.4, 8.6});

    BallCollider colliderB(Ball({5, 5}, 1.4));
    Entity entityB(colliderB, {5, 5}, {10.2, -13});

    hash.reserve_slots(2);
    hash.add_collider(entityA);
    hash.add_collider(entityB);

    CHECK(hash.get_entity_count() == 2);
}

TEST_CASE("SpatialHash detects collisions in nearby cells", "[SpatialHash]") {
    SpatialHash hash;

    BallCollider colliderA(Ball({16.7, 15.0}, 2.5));
    Entity entityA(colliderA, {16.7, 15.0}, {2.0, 2.0});

    BallCollider colliderB(Ball({17.0, 15.1}, 2.0)); //Collides with A
    Entity entityB(colliderB, {17.0, 15.1}, {-2.0, 2.2});

    BallCollider colliderC(Ball({10, 10}, 1.0)); //No collision
    Entity entityC(colliderC, {10, 10}, {0, 0});

    hash.add_collider(entityA);
    hash.add_collider(entityB);
    hash.add_collider(entityC);

    auto collisions = hash.get_collisions(entityA);
    REQUIRE(collisions.size() == 1);
    CHECK(collisions[0] == &entityB);
}

TEST_CASE("SpatialHash updates structure correctly on movement", "[SpatialHash]") {
    SpatialHash hash;

    BallCollider collider(Ball({22.2, 15.0}, 1.0));
    DummyEntity entity(collider, {22.2, 15.0}, {0, 0});
    hash.add_collider(entity);

    CHECK(hash.get_collisions(entity).empty());

    //Move the entity to a new cell
    entity.set_position({101, 122});
    hash.update_structure();

    //Should still have zero collisions
    auto collisions = hash.get_collisions(entity);
    CHECK(collisions.empty());
}

TEST_CASE("SpatialHash get_all_entities returns correct set", "[SpatialHash]") {
    SpatialHash hash;

    BallCollider colliderA(Ball({11, 11}, 4.4));
    Entity entityA(colliderA, {11, 11}, {12, 3.5});

    BallCollider colliderB(Ball({147, 152}, 1.0));
    Entity entityB(colliderB, {147, 152}, {6.6, -3.4});

    hash.add_collider(entityA);
    hash.add_collider(entityB);

    std::vector<EntityInterface*> collected;
    for (EntityInterface* e : hash.get_all_entities()) {
        collected.push_back(e);
    }

    REQUIRE(collected.size() == 2);
    CHECK((collected[0] == &entityA || collected[1] == &entityA));
    CHECK((collected[0] == &entityB || collected[1] == &entityB));
}

TEST_CASE("SweepAndPrune adds and counts distinct entities", "[SweepAndPrune]") {
    SweepAndPrune sap;

    BallCollider collider1(Ball({15.5, 20.4}, 2.5));
    Entity entity1(collider1, {15.5, 20.4}, {-4.5, 5.6});

    BallCollider collider2(Ball({45.1, 80.0}, 3.1));
    Entity entity2(collider2, {45.1, 80.0}, {-2.2, 7.3});

    sap.reserve_slots(2);
    sap.add_collider(entity1);
    sap.add_collider(entity2);

    CHECK(sap.get_entity_count() == 2);
    size_t count = 0;
    for (auto* entity : sap.get_all_entities()) {
        ++count;
    }
    CHECK(count == 4);
}

TEST_CASE("SweepAndPrune detects intended collision", "[SweepAndPrune]") {
    SweepAndPrune sap;

    BallCollider colliderA(Ball({10.2, 5.8}, 4.0));
    Entity entityA(colliderA, {10.2, 5.8}, {7.0, -1.0});

    BallCollider colliderB(Ball({13.2, 6.1}, 3.0)); // Overlaps with A
    Entity entityB(colliderB, {13.2, 6.1}, {0, 0});

    BallCollider colliderC(Ball({55.0, 107.0}, 5.9)); // Far away
    Entity entityC(colliderC, {55.0, 107.0}, {-1.2, 2.1});

    sap.add_collider(entityA);
    sap.add_collider(entityB);
    sap.add_collider(entityC);
    sap.post_bulk_add_callback();

    auto collisions = sap.get_all_collisions();
    REQUIRE(collisions.size() == 1);

    auto [e1, e2] = collisions.front();
    CHECK((e1 == &entityA && e2 == &entityB) || (e1 == &entityB && e2 == &entityA));
}

TEST_CASE("SweepAndPrune updates entity locations correctly", "[SweepAndPrune]") {
    SweepAndPrune sap;

    BallCollider collider(Ball({26.6, 31.0}, 7.6));
    Entity entity(collider, {26.6, 31.0}, {1.1, 1.8});
    sap.add_collider(entity);
    sap.post_bulk_add_callback();

    //Move entity on X-axis
    entity.set_position({90.0, 36.2});
    sap.update_structure();

    //Should not collide with old position
    auto collisions = sap.get_all_collisions();
    CHECK(collisions.empty());
}

TEST_CASE("SweepAndPrune get_all_entities returns correct pointers", "[SweepAndPrune]") {
    SweepAndPrune sap;

    BallCollider collider1(Ball({12.7, 8.0}, 1.3));
    Entity entity1(collider1, {12.7, 8.0}, {0, 0});

    BallCollider collider2(Ball({24.0, 16.1}, 2.2));
    Entity entity2(collider2, {24.0, 16.1}, {-1, 1});

    sap.add_collider(entity1);
    sap.add_collider(entity2);

    std::unordered_set<EntityInterface*> unique_entities;
    for (EntityInterface* e : sap.get_all_entities()) {
        unique_entities.insert(e);
    }

    CHECK(unique_entities.size() == 2);
    CHECK(unique_entities.contains(&entity1));
    CHECK(unique_entities.contains(&entity2));
}
*/
