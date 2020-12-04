#ifndef RAYTRACER_DIFFUSE_H
#define RAYTRACER_DIFFUSE_H

#include "Material.h"

namespace rt {
    class Diffuse : public Material {
    public:
        explicit Diffuse(Color3 albedo);

        bool scatter(const Ray &in, const hit &hit, Color3 &attenuation, Ray &out) const override;
    private:
        Color3 albedo;
    };
}

#endif //RAYTRACER_DIFFUSE_H
