#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"

namespace rt {
    class sphere : hittable {
    public:
        explicit sphere(vec3 position = vec3(), double radius = 1.0);
        sphere(double x, double y, double z, double radius = 1.0);

        [[nodiscard]] bool hit(const ray& r, struct hit& hit, double from, double to) const override;
    private:
        vec3 position;
        double radius;
    };
}

#endif //RAYTRACER_SPHERE_H
