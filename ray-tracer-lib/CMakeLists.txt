set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

set(HEADER_LIST
        include/rt/math/Vec3.h
        include/rt/math/Color3.h
        include/rt/math/Ray.h
        include/rt/objects/Hittable.h
        include/rt/objects/Sphere.h
        include/rt/math/Utils.h
        include/rt/graphics/Image.h
        include/rt/graphics/camera/Camera.h
        include/rt/graphics/camera/PerspectiveCamera.h
        include/rt/graphics/Scene.h
        include/rt/graphics/Renderer.h
        include/rt/materials/Material.h
        include/rt/materials/Diffuse.h
        include/rt/objects/Plane.h
        include/rt/math/Vec2.h
        include/rt/sampling/Vec2Sampling.h
        include/rt/sampling/Vec3Sampling.h
        include/rt/materials/Reflective.h
        include/rt/sampling/Sampler.h
        include/rt/utils/StringUtils.h
        include/rt/utils/ConcurrentUtils.h
        include/rt/utils/Printable.h)
set(SOURCE_LIST
        src/math/Vec3.cpp
        src/math/Color3.cpp
        src/math/Ray.cpp
        src/objects/Sphere.cpp
        src/graphics/Image.cpp
        src/graphics/camera/PerspectiveCamera.cpp
        src/graphics/Scene.cpp
        src/graphics/Renderer.cpp
        src/materials/Diffuse.cpp
        src/objects/Plane.cpp
        src/math/Vec2.cpp
        src/materials/Reflective.cpp)

add_library(rt ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(rt PRIVATE ../extern/stb)
target_include_directories(rt PUBLIC include)
target_link_libraries(rt PRIVATE spdlog::spdlog)

source_group(
        TREE "${RayTracer_SOURCE_DIR}/ray-tracer-lib/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
