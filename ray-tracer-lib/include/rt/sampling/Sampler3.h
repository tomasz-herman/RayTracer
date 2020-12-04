#ifndef RAYTRACER_SAMPLER3_H
#define RAYTRACER_SAMPLER3_H

#include <rt/math/Vec3.h>
#include <memory>
#include <functional>
#include <random>
#include <rt/math/Utils.h>

namespace rt {
    class Sampler3 {
    public:
        Sampler3(const std::function<std::unique_ptr<Vec3[]>(int)> &generator, int count, int sets = 1, const std::function<Vec3(Vec3)> &mapping = std::identity());
        [[nodiscard]] Vec3 get_sample();
        [[nodiscard]] Vec3 get_sample(int i) const;
        [[nodiscard]] int get_count() const;
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 rand = random_generator();
        std::unique_ptr<std::unique_ptr<Vec3[]>[]> samples;
        int count, current, sets, set;
    public:
        static std::unique_ptr<Vec3[]> dummy(int count);
        static std::unique_ptr<Vec3[]> random(int count);
        static std::unique_ptr<Vec3[]> regular(int count);
        static std::unique_ptr<Vec3[]> jitter(int count);
        static std::unique_ptr<Vec3[]> uniform_sphere(int count);
        static Vec3 wide_range(Vec3 sample);
    };
}

#endif //RAYTRACER_SAMPLER3_H
