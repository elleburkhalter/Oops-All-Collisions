cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(TowerDefenseCollision)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# Our Project
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

add_executable(tower_defense app/simulation_main.cpp)
#set(raylib_VERBOSE 1)
target_link_libraries(tower_defense raylib collision_core)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(tower_defense PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(tower_defense "-framework IOKit")
    target_link_libraries(tower_defense "-framework Cocoa")
    target_link_libraries(tower_defense "-framework OpenGL")
endif()
