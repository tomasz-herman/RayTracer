set(HEADER_LIST "${RayTracer_SOURCE_DIR}/include/ray-tracer-lib/math/vec3.h")

add_library(ray-tracer-lib math/vec3.cpp ${HEADER_LIST})

target_include_directories(ray-tracer-lib PUBLIC ../include)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
