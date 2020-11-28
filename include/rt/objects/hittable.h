#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "rt/math/ray.h"

namespace rt {
    struct hit {
        vec3 position;
        vec3 normal;
        double distance = 0;
    };

    class hittable {
    public:
        [[nodiscard]] virtual bool hit(const ray& r, hit& hit, double from, double to) const = 0;
    };
}

#endif //RAYTRACER_HITTABLE_H
