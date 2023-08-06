cmake_minimum_required(VERSION 3.14)
project(backgammon_test)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(.)
enable_testing()
include(GoogleTest)

# Board
file(GLOB board_SRC "board/*.h" "board/*.cpp")
add_library(board ${board_SRC})

# Board test
file(GLOB board_test_SRC "board_test/*.h" "board_test/*.cpp")
add_executable(board_test ${board_test_SRC})
target_link_libraries(board_test GTest::gtest_main board)
gtest_discover_tests(board_test)

# Main
file(GLOB backgammon_SRC "src/*.h" "src/*.cpp")
add_executable(backgammon ${backgammon_SRC})
target_link_libraries(backgammon board)
