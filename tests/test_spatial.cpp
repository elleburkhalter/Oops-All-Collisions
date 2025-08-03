#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <collision/BallCollider.h>
#include <spatial/Ball.h>
#include <data_structures/MultiLevelGrid.h>

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

TEST_CASE("MultiLevelGrid returns correct collision pairs", "[MultiLevelGrid]") {
    MultiLevelGrid grid;

    BallCollider colliderA(Ball({9.9, 9.9}, 11.3));
    AgentInterface entityA(colliderA);
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
    // MultiLevelGrid grid;
    //
    // Ball ball1({3.2, 6.1}, 2.0);
    // Ball ball2({4.7, 6.1}, 1.0);
    // Ball ball3({20.1, 22.9}, 3.0); //No collision
    //
    // BallCollider collider1(ball1);
    // BallCollider collider2(ball2);
    // BallCollider collider3(ball3);
    //
    // Entity entity1(collider1);
    // Entity entity2(collider2);
    // Entity entity3(collider3);
    //
    // grid.add_collider(entity1);
    // grid.add_collider(entity2);
    // grid.add_collider(entity3);
    //
    // auto collisions = grid.get_collisions(entity1);
    //
    // //Should detect entity2 as collision and NOT entity3
    // CHECK(std::find(collisions.begin(), collisions.end(), &entity2) != collisions.end());
    // CHECK(std::find(collisions.begin(), collisions.end(), &entity3) == collisions.end());
    //
    // //Collisions for entity3 should be empty
    // auto collisions_for_3 = grid.get_collisions(entity3);
    // CHECK(collisions_for_3.empty());
}
