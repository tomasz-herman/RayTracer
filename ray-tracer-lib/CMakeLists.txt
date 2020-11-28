set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

set(HEADER_LIST ../include/rt/math/vec3.h ../include/rt/math/color3.h ../include/rt/math/ray.h)
set(SOURCE_LIST src/math/vec3.cpp src/math/color3.cpp src/math/ray.cpp)

add_library(rt ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(rt PUBLIC "${RayTracer_SOURCE_DIR}/include")

source_group(
        TREE "${RayTracer_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
