set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

set(HEADER_LIST
        ../include/rt/math/vec3.h
        ../include/rt/math/color3.h
        ../include/rt/math/ray.h
        ../include/rt/objects/hittable.h
        ../include/rt/objects/sphere.h
        ../include/rt/math/utils.h
        ../include/rt/graphics/image.h
        ../include/rt/graphics/camera/camera.h
        ../include/rt/graphics/camera/perspective_camera.h)
set(SOURCE_LIST
        src/math/vec3.cpp
        src/math/color3.cpp
        src/math/ray.cpp
        src/objects/sphere.cpp
        src/graphics/image.cpp
        src/graphics/camera/perspective_camera.cpp)

add_library(rt ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(rt PUBLIC "${RayTracer_SOURCE_DIR}/include")

source_group(
        TREE "${RayTracer_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
