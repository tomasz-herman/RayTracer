#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <limits>
#include <random>
#include "Vec3.h"
#include <algorithm>
#include <thread>
#include <functional>
#include <vector>

namespace rt {
    static constexpr double INF = std::numeric_limits<double>::infinity();
    static constexpr double PI = 3.1415926535897932385;

    inline double deg_to_rad(double deg) {
        return deg * PI / 180.0;
    }

    inline double rad_to_deg(double rad) {
        return rad * 180.0 / PI;
    }

    inline std::mt19937 &random_generator() {
        static thread_local std::mt19937 gen(std::random_device{}());
        return gen;
    }

    static void parallel_for(unsigned nb_elements,
                      const std::function<void(int start, int end)> &functor,
                      bool use_threads = true) {
        unsigned int nb_threads_hint = std::thread::hardware_concurrency();
        unsigned int nb_threads = nb_threads_hint == 0 ? 8 : (nb_threads_hint);

        unsigned int batch_size = nb_elements / nb_threads;
        unsigned int batch_remainder = nb_elements % nb_threads;

        std::vector<std::thread> my_threads(nb_threads);

        if (use_threads) {
            for (unsigned i = 0; i < nb_threads; ++i) {
                unsigned int start = i * batch_size;
                my_threads[i] = std::thread(functor, start, start + batch_size);
            }
        } else {
            for (unsigned i = 0; i < nb_threads; ++i) {
                unsigned int start = i * batch_size;
                functor(start, start + batch_size);
            }
        }

        unsigned int start = nb_threads * batch_size;
        functor(start, start + batch_remainder);

        if (use_threads)
            std::for_each(my_threads.begin(), my_threads.end(), std::mem_fn(&std::thread::join));
    }
}

#endif //RAYTRACER_UTILS_H
