#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>
#include <rt/materials/Material.h>
#include "rt/math/Ray.h"

namespace rt {
    class Material;

    struct hit {
        Vec3 position;
        Vec3 normal;
        std::shared_ptr<Material> material_ptr;
        double distance = 0;
    };

    class Hittable {
    public:
        [[nodiscard]] virtual bool hit_test(const Ray& ray, hit& hit, double from, double to) const = 0;
    };
}

#endif //RAYTRACER_HITTABLE_H
