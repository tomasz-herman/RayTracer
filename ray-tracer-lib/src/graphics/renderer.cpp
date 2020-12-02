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
                for (int k = 0; k < samples; ++k) {
                    render(i, j) += shade(ray, scene, max_depth);
                }
            }
        }
        render.process([&](color3 c) { return c / samples; });
        spdlog::debug("Render finished in {:.3}s.", sw);
        return render;
    }

    color3 renderer::shade(const ray &r, const scene &scene, int depth) const {
        if(depth == 0) return color3::BLACK();

        hit hit;

        if(scene.hit_test(r, hit, 0.001, INF)) {
            ray scattered((vec3()), vec3());
            color3 attenuation;
            if(hit.material_ptr->scatter(r, hit, attenuation, scattered)) {
                return attenuation * shade(scattered, scene, depth - 1);
            }
            return color3::BLACK();
        }
        return color3::SKYBLUE() * (0.5 + (r.direction.y + 1) * 0.25);
    }

}
