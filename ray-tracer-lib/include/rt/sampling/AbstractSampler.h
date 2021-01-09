#ifndef RAYTRACER_ABSTRACTSAMPLER_H
#define RAYTRACER_ABSTRACTSAMPLER_H

namespace rt {
    template <class T>
    class AbstractSampler {
    public:
        AbstractSampler(const std::function<std::valarray<T>(int)> &generator, int count, int sets = 1, const std::function<T(T)> &mapping = std::identity()) : count(count), sets(sets) {
            samples = std::valarray<std::valarray<T>>(sets);
            for (int i = 0; i < sets; ++i) {
                samples[i] = generator(count);
                for (int j = 0; j < count; ++j) {
                    samples[i][j] = mapping(samples[i][j]);
                }
            }
        }

        [[nodiscard]] virtual T get_sample() = 0;

    protected:
        int count, sets;
        std::valarray<std::valarray<T>> samples;
    };
}

#endif //RAYTRACER_ABSTRACTSAMPLER_H
