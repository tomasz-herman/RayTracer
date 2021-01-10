#ifndef RAYTRACER_VEC2SAMPLING_H
#define RAYTRACER_VEC2SAMPLING_H

#include <rt/math/Vec2.h>
#include <functional>
#include <memory>
#include <rt/math/Utils.h>
#include <valarray>

namespace rt::Vec2Sampling {
    static std::valarray<Vec2> dummy(int count) {
        std::valarray<Vec2> samples = std::valarray<Vec2>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = samples[i].y = 0.5;
        }
        return samples;
    }

    static std::valarray<Vec2> random(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        std::valarray<Vec2> samples = std::valarray<Vec2>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = distribution(generator);
            samples[i].y = distribution(generator);
        }
        return samples;
    }

    static std::valarray<Vec2> regular(int count) {
        int size = ceil(sqrt(count));
        std::valarray<Vec2> samples = std::valarray<Vec2>(size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                samples[i * size + j].x = (i + 0.5) / size;
                samples[i * size + j].y = (j + 0.5) / size;
            }
        }
        return samples;
    }

    static std::valarray<Vec2> jitter(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        int size = ceil(sqrt(count));
        std::valarray<Vec2> samples = std::valarray<Vec2>(size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                samples[i * size + j].x = (i + distribution(generator)) / size;
                samples[i * size + j].y = (j + distribution(generator)) / size;
            }
        }
        return samples;
    }

    static Vec2 wide_range(Vec2 sample) {
        return Vec2(sample.x * 2 - 1, sample.y * 2 - 1);
    }

    static Vec2 to_disk(Vec2 sample) {
        sample = wide_range(sample);
        double r, phi;
        if(sample.x > -sample.y) {
            if(sample.x > sample.y) {
                r = sample.x;
                phi = sample.y / sample.x;
            } else {
                r = sample.y;
                phi = 2 - sample.x / sample.y;
            }
        } else {
            if(sample.x < sample.y) {
                r = -sample.x;
                phi = 4 + sample.y / sample.x;
            } else {
                r = -sample.y;
                phi = 6 - sample.x / sample.y;
            }
        }
        if(sample.x == 0 && sample.y == 0) {
            phi = 0;
        }
        phi *= PI / 4;
        return Vec2(r * cos(phi), r * sin(phi));
    }
}

#endif //RAYTRACER_VEC2SAMPLING_H
