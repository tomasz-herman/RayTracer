#ifndef RAYTRACER_SAMPLER_H
#define RAYTRACER_SAMPLER_H

#include "AbstractSampler.h"

namespace rt {
    template <class T>
    class Sampler : public AbstractSampler<T> {
    public:
        Sampler(const std::function<std::valarray<T>(int)> &generator, int count, int sets = 1, const std::function<T(T)> &mapping = std::identity()) : AbstractSampler<T>(generator, count, sets, mapping), sample(0), set(0) {
            distribution = std::uniform_int_distribution<int>(0, sets - 1);
        }

        [[nodiscard]] T get_sample() {
            if(sample >= AbstractSampler<T>::count) {
                sample = 0;
                if(AbstractSampler<T>::sets > 1) set = distribution(rand);
            }
            return AbstractSampler<T>::samples[set][sample++];
        }

    private:
        int sample, set;
        std::uniform_int_distribution<int> distribution;
        std::mt19937 rand = random_generator();
    };
}

#endif //RAYTRACER_SAMPLER_H
