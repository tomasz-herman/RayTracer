#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>
#include <rt/materials/material.h>
#include "rt/math/ray.h"

namespace rt {
    class material;

    struct hit {
        vec3 position;
        vec3 normal;
        std::shared_ptr<material> material_ptr;
        double distance = 0;
    };

    class hittable {
    public:
        [[nodiscard]] virtual bool hit_test(const ray& ray, hit& hit, double from, double to) const = 0;
    };
}

#endif //RAYTRACER_HITTABLE_H
