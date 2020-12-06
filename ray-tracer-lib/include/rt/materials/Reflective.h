#ifndef RAYTRACER_REFLECTIVE_H
#define RAYTRACER_REFLECTIVE_H

#include <rt/sampling/Sampler3.h>
#include "Material.h"

namespace rt {
    class Reflective : public Material {
    public:
        explicit Reflective(Color3 albedo, double fuzz = 0.0, Sampler3 sampler = Sampler3(Sampler3::uniform_sphere, 125, 8));

        bool scatter(const Ray &in, const hit &hit, Color3 &attenuation, Ray &out) override;
    private:
        Color3 albedo;
        double fuzz;
        Sampler3 sampler;
    };
}

#endif //RAYTRACER_REFLECTIVE_H
