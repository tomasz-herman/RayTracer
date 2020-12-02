#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include <rt/graphics/camera/camera.h>
#include "image.h"
#include "scene.h"

namespace rt {
    class renderer {
    public:
        renderer(int resolution, int samples, int max_depth);

        [[nodiscard]] image render(const scene& scene, const camera& camera) const;
        [[nodiscard]] color3 shade(const ray& ray, const scene& scene, int depth) const;
    private:
        int resolution;
        int samples;
        int max_depth;
    };
}

#endif //RAYTRACER_RENDERER_H
