#include <catch2/catch_test_macros.hpp>
#include <collision/BallCollider.h>
#include <spatial/Ball.h>
#include <data_structures/MultiLevelGrid.h>

//All test cases assume perfectly elastic

TEST_CASE("Collision conserves momentum and updates velocities correctly", "[ball_to_ball][velocity][momentum]") {
    Ball ballA({9.6, 8.0}, 7.0);
    Ball ballB({1.5, 8.7}, 2.5);

    BallCollider colliderA(ballA);
    BallCollider colliderB(ballB);

    colliderA.mass = 5.5;
    colliderB.mass = 2.6;

    colliderA.velocity = {3.0, 0.0};
    colliderB.velocity = {1.1, 3.3};

    //Initial total momentum
    Point initial_momentum = colliderA.mass * colliderA.velocity + colliderB.mass * colliderB.velocity;

    // Resolve collision
    CollisionCode code = colliderA.resolve_collision_with_ball(colliderB);
    REQUIRE(code == CollisionCode::COLLISION_PRESENT);

    //Total momentum after collision
    Point final_momentum = colliderA.mass * colliderA.velocity + colliderB.mass * colliderB.velocity;

    //Total momentum conserved
    REQUIRE(final_momentum.x == initial_momentum.x;
    REQUIRE(final_momentum.y == initial_momentum.y;

    //Correct final velocities
    REQUIRE(colliderA.velocity.x = Approx(1.78));
    REQUIRE(colliderB.velocity.x = Approx(3.68));
    REQUIRE(colliderA.velocity.y = Approx(2.12));
    REQUIRE(colliderB.velocity.y = Approx(-1.18));

    //Positions should move apart at least sum of radii
    double dist_after = Point::get_distance(colliderA.get_centroid(), colliderB.get_centroid());
    REQUIRE(dist_after >= ballA.radius + ballB.radius);
}

TEST_CASE("Collision updates velocities correctly", "[ball_to_ball][velocity]") {
    Ball ballA({14.6, 34.3}, 1.2);
    Ball ballB({15.2, 33.4}, 1.3);

    BallCollider colliderA(ballA);
    BallCollider colliderB(ballB);

    colliderA.mass = 0.6;
    colliderB.mass = 2.5;

    colliderA.velocity = {10.6, 5.3};
    colliderB.velocity = {2.2, 3.2};

    CollisionCode code = colliderA.resolve_collision_with_ball(colliderB);
    REQUIRE(code == CollisionCode::COLLISION_PRESENT);

    //Correct final velocities
    REQUIRE(colliderA.velocity.x = Approx(-2.95));
    REQUIRE(colliderB.velocity.x = Approx(5.45));
    REQUIRE(colliderA.velocity.y = Approx(1.91));
    REQUIRE(colliderB.velocity.y = Approx(4.01));
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
    REQUIRE(std::find(collisions.begin(), collisions.end(), &entity2) != collisions.end());
    REQUIRE(std::find(collisions.begin(), collisions.end(), &entity3) == collisions.end());

    //Collisions for entity3 should be empty
    auto collisions_for_3 = grid.get_collisions(entity3);
    REQUIRE(collisions_for_3.empty());
}
