#ifndef RAYTRACER_THREADSAFESAMPLER_H
#define RAYTRACER_THREADSAFESAMPLER_H

#include "AbstractSampler.h"

namespace rt {
    thread_local struct ThreadLocalFields {
        int sample = 0;
        int set = 0;
        std::mt19937 rand = random_generator();
    } ThreadLocalFields; // NOLINT(cert-err58-cpp)

    template <class T>
    class ThreadSafeSampler : public AbstractSampler<T> {
    public:
        ThreadSafeSampler(const std::function<std::valarray<T>(int)> &generator, int count, int sets = 1, const std::function<T(T)> &mapping = std::identity()) : AbstractSampler<T>(generator, count, sets, mapping) {}

        [[nodiscard]] T get_sample() {
            if(tlf.sample >= AbstractSampler<T>::count) {
                tlf.sample = 0;
                if(AbstractSampler<T>::sets > 1) tlf.set = distribution(tlf.rand);
            }
            return AbstractSampler<T>::samples[tlf.set][tlf.sample++];
        }

    private:
        std::uniform_int_distribution<int> distribution;
        struct ThreadLocalFields tlf;
    };
}

#endif //RAYTRACER_THREADSAFESAMPLER_H
