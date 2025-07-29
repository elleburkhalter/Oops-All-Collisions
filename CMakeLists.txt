cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Oops)

option(WITH_RAYLIB "Enable Raylib visualization" ON)
option(WITH_TESTS "Build unit tests" ON)

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
add_library(oops_collision_core
        src/spatial/Ball.cpp
        src/spatial/BoundingBox.cpp
        src/spatial/Point.cpp
        src/collision/BallCollider.cpp
)
target_include_directories(collision_core PUBLIC include)

if (WITH_RAYLIB)
    add_library(oops_rendering
            src/renderer/NullRenderer.cpp
            src/renderer/RaylibRenderer.cpp
    )
    add_executable(oops_executable app/simulation_main.cpp)
    target_link_libraries(oops_rendering PRIVATE oops_collision_core)
    target_include_directories(oops_rendering PUBLIC include)
else()
    add_library(oops_rendering
            src/renderer/NullRenderer.cpp
    )
    add_executable(oops_executable app/headless_main.cpp)
    target_link_libraries(oops_rendering PRIVATE oops_collision_core)
    target_include_directories(oops_rendering PUBLIC include)
endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(oops_executable PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(oops_executable "-framework IOKit")
    target_link_libraries(oops_executable "-framework Cocoa")
    target_link_libraries(oops_executable "-framework OpenGL")
endif()

if (WITH_TESTS)
    add_subdirectory(tests)
endif()
