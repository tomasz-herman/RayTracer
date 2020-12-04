#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <limits>
#include <random>
#include "Vec3.h"

namespace rt {
    static constexpr double INF = std::numeric_limits<double>::infinity();
    static constexpr double PI = 3.1415926535897932385;

    inline double deg_to_rad(double deg) {
        return deg * PI / 180.0;
    }

    inline double rad_to_deg(double rad) {
        return rad * 180.0 / PI;
    }

    inline double random_double() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator(std::random_device{}());
        return distribution(generator);
    }

    inline double random_double(double from, double to) {
        static std::uniform_real_distribution<double> distribution(from, to);
        static std::mt19937 generator(std::random_device{}());
        return distribution(generator);
    }

    inline static Vec3 random_vec3(double min, double max) {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    inline static Vec3 random_vec3_in_unit_sphere() {
        while (true) {
            auto p = random_vec3(-1,1);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    inline std::mt19937& random_generator() {
        static thread_local std::mt19937 gen(std::random_device{}());
        return gen;
    }
}

#endif //RAYTRACER_UTILS_H
