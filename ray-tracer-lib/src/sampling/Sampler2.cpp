#include <cmath>
#include <random>
#include "rt/sampling/Sampler2.h"

namespace rt {
    Sampler2::Sampler2(const std::function<std::unique_ptr<Vec2[]>(int)> &generator, int count, int sets, const std::function<Vec2(Vec2)> &mapping) : count(count), current(0), sets(sets), set(0) {
        distribution = std::uniform_int_distribution<int>(0, sets - 1);
        samples = std::make_unique<std::unique_ptr<Vec2[]>[]>(sets);
        for (int i = 0; i < sets; ++i) {
            samples[i] = generator(count);
            for (int j = 0; j < count; ++j) {
                samples[i][j] = mapping(samples[i][j]);
            }
        }
    }

    Vec2 Sampler2::get_sample() {
        if(current >= count) {
            current = 0;
            if(sets > 1) set = distribution(rand);
        }
        return samples[set][current++];
    }

    Vec2 Sampler2::get_sample(int i) const {
        return samples[set][i];
    }

    int Sampler2::get_count() const {
        return count;
    }

    std::unique_ptr<Vec2[]> Sampler2::dummy(int count) {
        std::unique_ptr<Vec2[]> samples = std::make_unique<Vec2[]>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = samples[i].y = 0.5;
        }
        return samples;
    }

    std::unique_ptr<Vec2[]> Sampler2::random(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        std::unique_ptr<Vec2[]> samples = std::make_unique<Vec2[]>(count);
        for (int i = 0; i < count; ++i) {
            samples[i].x = distribution(generator);
            samples[i].y = distribution(generator);
        }
        return samples;
    }

    std::unique_ptr<Vec2[]> Sampler2::regular(int count) {
        int size = ceil(sqrt(count));
        std::unique_ptr<Vec2[]> samples = std::make_unique<Vec2[]>(size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                samples[i * size + j].x = (i + 0.5) / size;
                samples[i * size + j].y = (j + 0.5) / size;
            }
        }
        return samples;
    }

    std::unique_ptr<Vec2[]> Sampler2::jitter(int count) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        int size = ceil(sqrt(count));
        std::unique_ptr<Vec2[]> samples = std::make_unique<Vec2[]>(size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                samples[i * size + j].x = (i + distribution(generator)) / size;
                samples[i * size + j].y = (j + distribution(generator)) / size;
            }
        }
        return samples;
    }

    Vec2 Sampler2::wide_range(Vec2 sample) {
        return Vec2(sample.x * 2 - 1, sample.y * 2 - 1);
    }

    Vec2 Sampler2::to_disk(Vec2 sample) {
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