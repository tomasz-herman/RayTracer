#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <rt/math/Ray.h>
#include <rt/objects/Hittable.h>
#include <rt/math/Color3.h>

namespace rt {
    class Hit;

    class Material {
    public:
        virtual bool scatter(const Ray& in, const Hit& hit, Color3& attenuation, Ray& out) = 0;
    };
}

#endif //RAYTRACER_MATERIAL_H
