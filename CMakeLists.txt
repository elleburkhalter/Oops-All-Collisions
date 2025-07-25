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
        # ADD PROJECT SOURCE FILES EXCEPT RENDERING HERE
)
target_include_directories(collision_core PUBLIC include)

# ===== Visualization library =====
if(WITH_SFML)
    add_library(collision_rendering
            src/rendering/SFMLRenderer.cpp
            src/rendering/NullRenderer.cpp
    )
    target_link_libraries(collision_rendering PRIVATE collision_core SFML::Graphics)
    target_include_directories(collision_rendering PUBLIC include)
else()
    add_library(collision_rendering
            src/rendering/NullRenderer.cpp
    )
    target_link_libraries(collision_rendering PRIVATE collision_core)
    target_include_directories(collision_rendering PUBLIC include)
endif()

# ===== Main executable =====
add_executable(tower_defense apps/simulation_main.cpp)
target_link_libraries(tower_defense PRIVATE collision_core collision_rendering)

# ===== Tests =====
if(WITH_TESTS)
    add_subdirectory(tests)
endif()