#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <rt/math/ray.h>
#include <rt/objects/hittable.h>
#include <rt/math/color3.h>

namespace rt {
    class hit;
    class material {
    public:
        virtual bool scatter(const ray& in, const hit& hit, color3& attenuation, ray& out) const = 0;
    };
}

#endif //RAYTRACER_MATERIAL_H
