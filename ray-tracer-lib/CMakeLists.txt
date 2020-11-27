set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(HEADER_LIST "${RayTracer_SOURCE_DIR}/include/rt/math/vec3.h")

add_library(rt src/math/vec3.cpp ${HEADER_LIST})

target_include_directories(rt PUBLIC "${RayTracer_SOURCE_DIR}/include")

source_group(
        TREE "${RayTracer_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
