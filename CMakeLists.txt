cmake_minimum_required(VERSION 3.15)
project(TowerDefenseCollision)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_SFML "Enable SFML visualization" ON)
option(WITH_TESTS "Build unit tests" ON)

include(FetchContent)

# ===== Fetch SFML if visualization is enabled =====
if(WITH_SFML)
    FetchContent_Declare(
            sfml
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 3.0.1
    )
    FetchContent_MakeAvailable(sfml)
endif()

# ===== Core library =====
add_library(collision_core
        src/spatial/Ball.cpp
        src/spatial/BoundingBox.cpp
        src/spatial/Point.cpp
        src/renderer/NullRenderer.cpp
        include/spatial/RegionInterface.h
        include/collision/ColliderInterface.h
        include/collision/ColliderFlags.h
        include/collision/BallCollider.h
        src/collision/BallCollider.cpp
        include/game_object/base/EntityABC.h
        include/game_object/base/AgentABC.h
        include/game_object/base/ProjectileABC.h
)
target_include_directories(collision_core PUBLIC include)

# ===== Visualization library =====
if(WITH_SFML)
    add_library(collision_renderer
            src/renderer/SFMLRenderer.cpp
            src/renderer/NullRenderer.cpp
            include/ui_object/Text.h
    )
    target_link_libraries(collision_renderer PRIVATE collision_core SFML::Graphics)
    target_include_directories(collision_renderer PUBLIC include)
else()
    add_library(collision_renderer
            src/renderer/NullRenderer.cpp
    )
    target_link_libraries(collision_renderer PRIVATE collision_core)
    target_include_directories(collision_renderer PUBLIC include)
endif()

# ===== Main executable =====
add_executable(tower_defense app/simulation_main.cpp)
target_link_libraries(tower_defense PRIVATE collision_core collision_renderer)

# ===== Tests =====
if(WITH_TESTS)
    add_subdirectory(tests)
endif()