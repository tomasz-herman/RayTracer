#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"

namespace rt {
    class sphere : public hittable {
    public:
        explicit sphere(std::shared_ptr<material> material_ptr, vec3 position = vec3(), double radius = 1.0);
        sphere(std::shared_ptr<material> material_ptr, double x, double y, double z, double radius = 1.0);

        [[nodiscard]] bool hit_test(const ray& ray, hit& hit, double from, double to) const override;
    private:
        vec3 position;
        double radius;
        std::shared_ptr<material> material_ptr;
    };
}

#endif //RAYTRACER_SPHERE_H
