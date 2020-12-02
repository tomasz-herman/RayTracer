#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "hittable.h"

namespace rt {
    class plane : public hittable {
    public:
        explicit plane(std::shared_ptr<material> material_ptr, vec3 position = vec3(), vec3 normal = vec3(0, 1, 0));

        bool hit_test(const ray &ray, hit &hit, double from, double to) const override;
    private:
        vec3 position;
        vec3 normal;
        std::shared_ptr<material> material_ptr;
    };
}

#endif //RAYTRACER_PLANE_H
