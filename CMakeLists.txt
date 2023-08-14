cmake_minimum_required(VERSION 3.14)
project(Backgammon)

include(FetchContent)
# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.2)

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

find_package(OpenMP REQUIRED)

include_directories(.)
enable_testing()
include(GoogleTest)

# Core
file(GLOB core_SRC "core/*.h" "core/*.cpp")
add_library(core ${core_SRC})

# Core test
file(GLOB core_test_SRC "core_test/*.h" "core_test/*.cpp")
add_executable(core_test ${core_test_SRC})
target_link_libraries(core_test GTest::gtest_main core)
gtest_discover_tests(core_test)

# Search
file(GLOB search_SRC "search/*.h" "search/*.cpp")
add_library(search ${search_SRC})
target_link_libraries(search core OpenMP::OpenMP_CXX)

# Search test
file(GLOB search_test_SRC "search_test/*.h" "search_test/*.cpp")
add_executable(search_test ${search_test_SRC})
target_link_libraries(search_test GTest::gtest_main search)
gtest_discover_tests(search_test)

# Search benchmark
file(GLOB search_benchmark_SRC "search_benchmark/*.h" "search_benchmark/*.cpp")
add_executable(search_benchmark ${search_benchmark_SRC})
target_link_libraries(search_benchmark benchmark::benchmark search)

# Perft
file(GLOB perft_SRC "perft/*.h" "perft/*.cpp")
add_executable(perft ${perft_SRC})
target_link_libraries(perft core OpenMP::OpenMP_CXX)

# Hyper
file(GLOB hyper_SRC "hyper/*.h" "hyper/*.cpp")
add_executable(hyper ${hyper_SRC})
target_link_libraries(hyper core search)

# Backgammon
file(GLOB backgammon_SRC "src/*.h" "src/*.cpp")
add_executable(backgammon ${backgammon_SRC})
target_link_libraries(backgammon core)


# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET core core_test search search_test search_benchmark perft hyper backgammon PROPERTY CXX_STANDARD 23)