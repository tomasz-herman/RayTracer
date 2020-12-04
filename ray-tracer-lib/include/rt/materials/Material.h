#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <rt/math/Ray.h>
#include <rt/objects/Hittable.h>
#include <rt/math/Color3.h>

namespace rt {
    class hit;
    class Material {
    public:
        virtual bool scatter(const Ray& in, const hit& hit, Color3& attenuation, Ray& out) const = 0;
    };
}

#endif //RAYTRACER_MATERIAL_H
