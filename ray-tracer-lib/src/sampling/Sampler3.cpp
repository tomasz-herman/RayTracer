#include <random>
#include <iostream>
#include "rt/sampling/Sampler3.h"

namespace rt {
    Sampler3::Sampler3(const std::function<std::valarray<Vec3>(int)> &generator, int count, int sets, const std::function<Vec3(Vec3)> &mapping) : count(count), current(0), sets(sets), set(0) {
        distribution = std::uniform_int_distribution<int>(0, sets - 1);
        samples = std::valarray<std::valarray<Vec3>>(sets);
        for (int i = 0; i < sets; ++i) {
            samples[i] = generator(count);
            for (int j = 0; j < count; ++j) {
                samples[i][j] = mapping(samples[i][j]);
            }
        }
    }

    Vec3 Sampler3::get_sample() {
        if(current >= count) {
            current = 0;
            if(sets > 1) set = distribution(rand);
        }
        return samples[set][current++];
    }

    Vec3 Sampler3::get_sample(int i) const {
        return samples[set][i];
    }

    int Sampler3::get_count() const {
        return count;
    }

    std::valarray<Vec3> Sampler3::dummy(int count) {
        std::valarray<Vec3> samples = std::valarray<Vec3>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = samples[i].y = samples[i].z = 0.5;
        }
        return samples;
    }

    std::valarray<Vec3> Sampler3::random(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        std::valarray<Vec3> samples = std::valarray<Vec3>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = distribution(generator);
            samples[i].y = distribution(generator);
            samples[i].z = distribution(generator);
        }
        return samples;
    }

    std::valarray<Vec3> Sampler3::regular(int count) {
        int size = ceil(cbrt(count));
        std::valarray<Vec3> samples = std::valarray<Vec3>(size * size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    samples[i * size * size + j * size + k].x = (i + 0.5) / size;
                    samples[i * size * size + j * size + k].y = (j + 0.5) / size;
                    samples[i * size * size + j * size + k].z = (k + 0.5) / size;
                }
            }
        }
        return samples;
    }

    std::valarray<Vec3> Sampler3::jitter(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        int size = ceil(cbrt(count));
        std::valarray<Vec3> samples = std::valarray<Vec3>(size * size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    samples[i * size * size + j * size + k].x = (i + distribution(generator)) / size;
                    samples[i * size * size + j * size + k].y = (j + distribution(generator)) / size;
                    samples[i * size * size + j * size + k].z = (k + distribution(generator)) / size;
                }
            }
        }
        return samples;
    }

    std::valarray<Vec3> Sampler3::uniform_sphere(int count) {
        std::normal_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        std::valarray<Vec3> samples = std::valarray<Vec3>(count);
        for (int i = 0; i < count; ++i) {
            double x = distribution(generator);
            double y = distribution(generator);
            double z = distribution(generator);
            double v = distribution(generator);
            double w = distribution(generator);
            double norm = sqrt(x * x + y * y + z * z + w * w + v * v);
            samples[i] = Vec3(x, y, z) / norm;
        }
        return samples;
    }

    Vec3 Sampler3::wide_range(Vec3 sample) {
        return Vec3(sample.x * 2 - 1, sample.y * 2 - 1, sample.z * 2 - 1);
    }

}