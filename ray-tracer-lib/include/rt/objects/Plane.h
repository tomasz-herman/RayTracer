#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Hittable.h"

namespace rt {
    class Plane : public Hittable {
    public:
        explicit Plane(std::shared_ptr<Material> material_ptr, Vec3 position = Vec3(), Vec3 normal = Vec3(0, 1, 0));

        bool hit_test(const Ray &ray, Hit &hit, double from, double to) const override;
        void print(std::ostream& stream, int indent) const override;
    private:
        Vec3 position;
        Vec3 normal;
        std::shared_ptr<Material> material_ptr;
    };
}

#endif //RAYTRACER_PLANE_H
