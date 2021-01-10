#include <rt/math/Utils.h>
#include "rt/materials/Diffuse.h"

namespace rt {
    Diffuse::Diffuse(Color3 albedo, Sampler<Vec3> sampler) : albedo(albedo), sampler(std::move(sampler)) { }

    bool Diffuse::scatter(const Ray &in, const Hit &hit, Color3 &attenuation, Ray &out) {
        Vec3 dir = hit.normal + sampler.get_sample();
        out = Ray(hit.position, dir);
        attenuation = albedo;
        return true;
    }
}