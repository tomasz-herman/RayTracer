#include <rt/math/Utils.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include <rt/math/Vec2.h>
#include <rt/sampling/Vec2Sampling.h>
#include <rt/sampling/Sampler.h>
#include <rt/utils/ConcurrentUtils.h>
#include "rt/graphics/Renderer.h"
#include <fmt/ostream.h>

namespace rt {
    Renderer::Renderer(int resolution, int samples, int max_depth) : resolution(resolution), samples(samples), max_depth(max_depth) { }

    Image Renderer::render(const Scene& scene, const Camera& camera, bool use_threads) const {
        Sampler<Vec2> sampler = Sampler<Vec2>(Vec2Sampling::jitter, samples);
        int width = resolution;
        int height = static_cast<int>(resolution / camera.get_aspect());
        Image render(width, height);
        spdlog::info("Rendering scene to image. Using {} samples. Max depth is {}. Resolution is {}x{}.", samples, max_depth, width, height);
        spdlog::info("The scene is: \n{}", scene);
        spdlog::stopwatch sw;
        parallel_for(width, [&](int start, int end){
            for(int i = start; i < end; ++i) {
                for(int j = 0; j < height; j++) {
                    for (int k = 0; k < samples; ++k) {
                        Vec2 sample = sampler.get_sample();
                        double u = (double) (i + sample.x) / (width - 1);
                        double v = (double) (j + sample.y) / (height - 1);
                        Ray ray = camera.get_ray(u, v);
                        render(i, j) += shade(ray, scene, max_depth);
                    }
                }
            }
        }, use_threads);
        render.process([&](Color3 c) { return c / samples; });
        spdlog::info("Render finished in {:.3}s.", sw);
        return render;
    }

    Color3 Renderer::shade(const Ray &ray, const Scene &scene, int depth) const {
        if(depth == 0) return Color3::BLACK();

        Hit hit;

        if(scene.hit_test(ray, hit, 0.001, INF)) {
            Ray scattered((Vec3()), Vec3());
            Color3 attenuation;
            if(hit.material_ptr->scatter(ray, hit, attenuation, scattered)) {
                return attenuation * shade(scattered, scene, depth - 1);
            }
            return Color3::BLACK();
        }
        return scene.get_sky_color();
    }

}
