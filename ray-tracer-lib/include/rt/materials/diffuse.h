#ifndef RAYTRACER_DIFFUSE_H
#define RAYTRACER_DIFFUSE_H

#include "material.h"

namespace rt {
    class diffuse : public material {
    public:
        explicit diffuse(color3 albedo);

        bool scatter(const ray &in, const hit &hit, color3 &attenuation, ray &out) const override;
    private:
        color3 albedo;
    };
}

#endif //RAYTRACER_DIFFUSE_H
