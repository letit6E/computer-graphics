cmake_minimum_required(VERSION 3.22)
project(maze)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests tests/maze_tests.cpp
        src/maze/maze.hpp
        src/maze/point.hpp
        src/wavelet_tree/wavelet-tree.hpp
        src/wavelet_tree/wavelet-tree.hpp
        tests/wavelet_tests.cpp
        tests/wavelet_tests.cpp
        src/interval_tree/maze-segment.hpp
        src/interval_tree/interval-tree.hpp
        src/interval_tree/interval-tree.hpp
        tests/interval_tests.cpp
        tests/interval_tests.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)