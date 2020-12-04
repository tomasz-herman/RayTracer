#include <rt/math/Utils.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include "rt/graphics/Renderer.h"

namespace rt {
    Renderer::Renderer(int resolution, int samples, int max_depth) : resolution(resolution), samples(samples), max_depth(max_depth) { }

    Image Renderer::render(const Scene& scene, const Camera& camera) const {
        int width = resolution;
        int height = static_cast<int>(resolution / camera.get_aspect());
        Image render(width, height);
        spdlog::debug("Rendering scene to image. Using {} samples. Max depth is {}. Resolution is {}x{}.", samples, max_depth, width, height);
        spdlog::stopwatch sw;
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                double u = (double) i / (width - 1);
                double v = (double) j / (height - 1);
                Ray ray = camera.get_ray(u, v);
                for (int k = 0; k < samples; ++k) {
                    render(i, j) += shade(ray, scene, max_depth);
                }
            }
        }
        render.process([&](Color3 c) { return c / samples; });
        spdlog::debug("Render finished in {:.3}s.", sw);
        return render;
    }

    Color3 Renderer::shade(const Ray &r, const Scene &scene, int depth) const {
        if(depth == 0) return Color3::BLACK();

        hit hit;

        if(scene.hit_test(r, hit, 0.001, INF)) {
            Ray scattered((Vec3()), Vec3());
            Color3 attenuation;
            if(hit.material_ptr->scatter(r, hit, attenuation, scattered)) {
                return attenuation * shade(scattered, scene, depth - 1);
            }
            return Color3::BLACK();
        }
        return scene.get_sky_color() * (0.5 + (r.direction.y + 1) * 0.25);
    }

}
