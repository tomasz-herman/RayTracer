#include <rt/math/utils.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include "rt/graphics/renderer.h"

namespace rt {
    renderer::renderer(int resolution, int samples, int max_depth) : resolution(resolution), samples(samples), max_depth(max_depth) { }

    image renderer::render(const scene& scene, const camera& camera) const {
        int width = resolution;
        int height = static_cast<int>(resolution / camera.get_aspect());
        image render(width, height);
        spdlog::debug("Rendering scene to image. Using {} samples. Max depth is {}. Resolution is {}x{}.", samples, max_depth, width, height);
        spdlog::stopwatch sw;
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
        spdlog::debug("Render finished in {:.3}s.", sw);
        return render;
    }

}
