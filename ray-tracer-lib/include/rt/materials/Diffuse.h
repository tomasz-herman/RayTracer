#ifndef RAYTRACER_DIFFUSE_H
#define RAYTRACER_DIFFUSE_H

#include <rt/sampling/Vec3Sampling.h>
#include <rt/sampling/Sampler.h>
#include "Material.h"

namespace rt {
    class Diffuse : public Material {
    public:
        explicit Diffuse(Color3 albedo, Sampler<Vec3> sampler = Sampler<Vec3>(Vec3Sampling::uniform_sphere, 125, 8));

        bool scatter(const Ray &in, const Hit &hit, Color3 &attenuation, Ray &out) override;
    private:
        Color3 albedo;
        Sampler<Vec3> sampler;
    };
}

#endif //RAYTRACER_DIFFUSE_H
