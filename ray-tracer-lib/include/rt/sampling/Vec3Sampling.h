#ifndef RAYTRACER_VEC3SAMPLING_H
#define RAYTRACER_VEC3SAMPLING_H

#include <rt/math/Vec3.h>
#include <memory>
#include <functional>
#include <random>
#include <rt/math/Utils.h>
#include <valarray>

namespace rt::Vec3Sampling {
    static std::valarray<Vec3> dummy(int count) {
        std::valarray<Vec3> samples = std::valarray<Vec3>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = samples[i].y = samples[i].z = 0.5;
        }
        return samples;
    }

    static std::valarray<Vec3> random(int count) {
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

    static std::valarray<Vec3> regular(int count) {
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

    static std::valarray<Vec3> jitter(int count) {
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

    static std::valarray<Vec3> uniform_sphere(int count) {
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

    static Vec3 wide_range(Vec3 sample) {
        return Vec3(sample.x * 2 - 1, sample.y * 2 - 1, sample.z * 2 - 1);
    }
}


#endif //RAYTRACER_VEC3SAMPLING_H
