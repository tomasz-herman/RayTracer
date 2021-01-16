#ifndef RAYTRACER_CONCURRENTUTILS_H
#define RAYTRACER_CONCURRENTUTILS_H

namespace rt {
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

#endif //RAYTRACER_CONCURRENTUTILS_H
