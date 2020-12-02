set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

set(HEADER_LIST
        include/rt/math/vec3.h
        include/rt/math/color3.h
        include/rt/math/ray.h
        include/rt/objects/hittable.h
        include/rt/objects/sphere.h
        include/rt/math/utils.h
        include/rt/graphics/image.h
        include/rt/graphics/camera/camera.h
        include/rt/graphics/camera/perspective_camera.h
        include/rt/graphics/scene.h
        include/rt/graphics/renderer.h
        include/rt/materials/material.h
        include/rt/materials/diffuse.h)
set(SOURCE_LIST
        src/math/vec3.cpp
        src/math/color3.cpp
        src/math/ray.cpp
        src/objects/sphere.cpp
        src/graphics/image.cpp
        src/graphics/camera/perspective_camera.cpp
        src/graphics/scene.cpp
        src/graphics/renderer.cpp
        src/materials/diffuse.cpp)

add_library(rt ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(rt PRIVATE ../extern/stb)
target_include_directories(rt PUBLIC include)
target_link_libraries(rt PRIVATE spdlog::spdlog)

source_group(
        TREE "${RayTracer_SOURCE_DIR}/ray-tracer-lib/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
