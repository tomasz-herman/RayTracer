cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(RayTracer src/main.cpp)

target_link_libraries(RayTracer pthread)