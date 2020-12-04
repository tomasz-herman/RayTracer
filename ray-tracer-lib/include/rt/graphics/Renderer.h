#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include <rt/graphics/camera/Camera.h>
#include "Image.h"
#include "Scene.h"

namespace rt {
    class Renderer {
    public:
        Renderer(int resolution, int samples, int max_depth);

        [[nodiscard]] Image render(const Scene& scene, const Camera& camera) const;
        [[nodiscard]] Color3 shade(const Ray& ray, const Scene& scene, int depth) const;
    private:
        int resolution;
        int samples;
        int max_depth;
    };
}

#endif //RAYTRACER_RENDERER_H
