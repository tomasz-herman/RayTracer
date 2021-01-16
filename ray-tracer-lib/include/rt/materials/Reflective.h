#ifndef RAYTRACER_REFLECTIVE_H
#define RAYTRACER_REFLECTIVE_H

#include <rt/sampling/Vec3Sampling.h>
#include <rt/sampling/Sampler.h>
#include "Material.h"

namespace rt {
    class Reflective : public Material {
    public:
        explicit Reflective(Color3 albedo, double fuzz = 0.0, Sampler<Vec3> sampler = Sampler<Vec3>(Vec3Sampling::uniform_sphere, 125, 1));

        bool scatter(const Ray &in, const Hit &hit, Color3 &attenuation, Ray &out) override;
    protected: void print(std::ostream& stream, int indent) const override;
    private:
        Color3 albedo;
        double fuzz;
        Sampler<Vec3> sampler;
    };
}

#endif //RAYTRACER_REFLECTIVE_H
