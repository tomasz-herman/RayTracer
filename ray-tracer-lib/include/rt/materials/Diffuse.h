#ifndef RAYTRACER_DIFFUSE_H
#define RAYTRACER_DIFFUSE_H

#include <rt/sampling/Sampler3.h>
#include "Material.h"

namespace rt {
    class Diffuse : public Material {
    public:
        explicit Diffuse(Color3 albedo, Sampler3 sampler = Sampler3(Sampler3::uniform_sphere, 125, 8));

        bool scatter(const Ray &in, const hit &hit, Color3 &attenuation, Ray &out) override;
    private:
        Color3 albedo;
        Sampler3 sampler;
    };
}

#endif //RAYTRACER_DIFFUSE_H
