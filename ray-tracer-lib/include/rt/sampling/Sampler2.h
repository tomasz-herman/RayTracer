#ifndef RAYTRACER_SAMPLER2_H
#define RAYTRACER_SAMPLER2_H

#include <rt/math/Vec2.h>
#include <functional>
#include <memory>
#include <rt/math/Utils.h>

namespace rt {
    class Sampler2 {
    public:
        Sampler2(const std::function<std::unique_ptr<Vec2[]>(int)> &generator, int count, int sets = 1, const std::function<Vec2(Vec2)> &mapping = std::identity());
        [[nodiscard]] Vec2 get_sample();
        [[nodiscard]] Vec2 get_sample(int i) const;
        [[nodiscard]] int get_count() const;
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 rand = random_generator();
        std::unique_ptr<std::unique_ptr<Vec2[]>[]> samples;
        int count, current, sets, set;
    public:
        static std::unique_ptr<Vec2[]> dummy(int count);
        static std::unique_ptr<Vec2[]> random(int count);
        static std::unique_ptr<Vec2[]> regular(int count);
        static std::unique_ptr<Vec2[]> jitter(int count);
        static Vec2 wide_range(Vec2 sample);
        static Vec2 to_disk(Vec2 sample);
    };
}

#endif //RAYTRACER_SAMPLER2_H
