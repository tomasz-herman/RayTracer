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
}

#endif //RAYTRACER_UTILS_H
