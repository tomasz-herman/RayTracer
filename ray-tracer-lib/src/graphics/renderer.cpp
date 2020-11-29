#include <rt/math/utils.h>
#include "rt/graphics/renderer.h"

namespace rt {
    renderer::renderer(int resolution, int samples, int max_depth) : resolution(resolution), samples(samples), max_depth(max_depth) { }

    image renderer::render(const scene& scene, const camera& camera) const {
        int width = resolution;
        int height = static_cast<int>(resolution / camera.get_aspect());
        image render(width, height);
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                double u = (double) i / (width - 1);
                double v = (double) j / (height - 1);
                ray ray = camera.get_ray(u, v);
                hit hit;
                if(scene.hit_test(ray, hit, 0.0001, INF)) {
                    render(i, j) = color3::CADETBLUE();
                }
            }
        }
        return render;
    }

}
