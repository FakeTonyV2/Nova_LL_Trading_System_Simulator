cmake_minimum_required(VERSION 3.20)
project(nova_l2 LANGUAGES CXX)

option(NOVA_BUILD_TESTS "Build unit tests" ON)
option(NOVA_BUILD_BENCHMARKS "Build the lightweight benchmark" ON)
option(NOVA_ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(nova_core
    src/FeedHandler.cpp
    src/Gateway.cpp
    src/Matcher.cpp
    src/OrderBook.cpp
    src/OrderPool.cpp
    src/PriceLevelPool.cpp
)
target_include_directories(nova_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(nova_core PRIVATE -Wall -Wextra -Wpedantic)
if(NOVA_ENABLE_SANITIZERS)
    target_compile_options(nova_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(nova_core PUBLIC -fsanitize=address,undefined)
endif()

add_executable(nova_replay src/main.cpp)
target_link_libraries(nova_replay PRIVATE nova_core)

if(NOVA_BUILD_TESTS)
    enable_testing()
    add_executable(nova_tests tests/nova_tests.cpp)
    target_link_libraries(nova_tests PRIVATE nova_core)
    add_test(NAME nova_tests COMMAND nova_tests)
endif()

if(NOVA_BUILD_BENCHMARKS)
    add_executable(nova_benchmark benchmarks/matcher_benchmark.cpp)
    target_link_libraries(nova_benchmark PRIVATE nova_core)
endif()
