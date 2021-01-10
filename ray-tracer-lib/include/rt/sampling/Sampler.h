#ifndef RAYTRACER_SAMPLER_H
#define RAYTRACER_SAMPLER_H

namespace rt {
    inline thread_local struct ThreadLocalFields {
        int sample = 0;
        int set = 0;
        std::mt19937 rand = random_generator();
    } ThreadLocalFields; // NOLINT(cert-err58-cpp)

    template <class T>
    class Sampler {
    public:
        Sampler(const std::function<std::valarray<T>(int)> &generator, int count, int sets = 1, const std::function<T(T)> &mapping = std::identity()) : count(count), sets(sets) {
            distribution = std::uniform_int_distribution<int>(0, sets - 1);
            samples = std::valarray<std::valarray<T>>(sets);
            for (int i = 0; i < sets; ++i) {
                samples[i] = generator(count);
                for (int j = 0; j < count; ++j) {
                    samples[i][j] = mapping(samples[i][j]);
                }
            }
        }

        [[nodiscard]] T get_sample() {
            if(tlf.sample >= count) {
                tlf.sample = 0;
                if(sets > 1) tlf.set = distribution(tlf.rand);
            }
            return samples[tlf.set][tlf.sample++];
        }

    private:
        std::uniform_int_distribution<int> distribution;
        struct ThreadLocalFields tlf;
        int count, sets;
        std::valarray<std::valarray<T>> samples;
    };
}

#endif //RAYTRACER_SAMPLER_H
