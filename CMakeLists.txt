cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(ray-tracer-demo)
add_subdirectory(ray-tracer-lib)

option(PACKAGE_TESTS "Build the tests" ON)

if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(ray-tracer-test)
endif()