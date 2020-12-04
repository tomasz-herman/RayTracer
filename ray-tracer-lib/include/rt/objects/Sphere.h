#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"

namespace rt {
    class Sphere : public Hittable {
    public:
        explicit Sphere(std::shared_ptr<Material> material_ptr, Vec3 position = Vec3(), double radius = 1.0);
        Sphere(std::shared_ptr<Material> material_ptr, double x, double y, double z, double radius = 1.0);

        [[nodiscard]] bool hit_test(const Ray& ray, hit& hit, double from, double to) const override;
    private:
        Vec3 position;
        double radius;
        std::shared_ptr<Material> material_ptr;
    };
}

#endif //RAYTRACER_SPHERE_H
