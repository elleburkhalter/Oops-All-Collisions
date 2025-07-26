# tests/CMakeLists.txt
include(FetchContent)

# ===== Fetch Catch2 =====
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.0
)
FetchContent_MakeAvailable(catch2)

# ===== Collect tests =====
set(TEST_SOURCES
        test_spatial.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests
        PRIVATE collision_core Catch2::Catch2WithMain
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ===== Register with CTest =====
include(CTest)
include(Catch)
catch_discover_tests(run_tests)