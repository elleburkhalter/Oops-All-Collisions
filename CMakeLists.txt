cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0135 NEW)
project(Oops)

option(WITH_RAYLIB "Enable Raylib visualization" ON)
option(WITH_TESTS "Build unit tests" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WITH_RAYLIB)
    # Dependencies
    set(RAYLIB_VERSION 5.5)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Core library
add_library(oops_core
        src/spatial/Ball.cpp
        src/spatial/BoundingBox.cpp
        src/spatial/Point.cpp
        src/collision/BallCollider.cpp
        src/data_structures/BoundingVolumeHierarchy.cpp
        src/data_structures/MultiLevelGrid.cpp
        src/data_structures/NaiveLinear.cpp
        src/data_structures/SpatialHash.cpp
        src/data_structures/SweepAndPrune.cpp
)
target_include_directories(oops_core PUBLIC include)

# Statistics tracking/logging library
add_library(oops_statistics
        src/statistics/LoggerStatistics.cpp
        src/statistics/NullStatistics.cpp
)
target_link_libraries(oops_statistics PUBLIC oops_core)
target_include_directories(oops_statistics PUBLIC include)

# Rendering & executable
if (WITH_RAYLIB)
    add_library(oops_rendering
            src/renderer/NullRenderer.cpp
            src/renderer/RaylibRenderer.cpp
    )
    target_link_libraries(oops_rendering PUBLIC oops_core raylib)
    target_include_directories(oops_rendering PUBLIC include)

    add_executable(oops_executable app/simulation_main.cpp)
    target_link_libraries(oops_executable PRIVATE oops_rendering oops_statistics)
else()
    add_library(oops_rendering src/renderer/NullRenderer.cpp)
    target_link_libraries(oops_rendering PUBLIC oops_core)
    target_include_directories(oops_rendering PUBLIC include)

    add_executable(oops_executable app/headless_main.cpp)
    target_link_libraries(oops_executable PRIVATE oops_rendering oops_statistics)
endif()

# Mac frameworks
if (APPLE)
    target_link_libraries(oops_executable PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(oops_executable PROPERTIES SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

if (WITH_TESTS)
    add_subdirectory(tests)
endif()