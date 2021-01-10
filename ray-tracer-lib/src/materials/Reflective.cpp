#include "rt/materials/Reflective.h"

namespace rt {

    Reflective::Reflective(Color3 albedo, double fuzz, Sampler<Vec3> sampler) : albedo(albedo), fuzz(fuzz), sampler(std::move(sampler)) { }

    bool Reflective::scatter(const Ray &in, const hit &hit, Color3 &attenuation, Ray &out) {
        Vec3 reflected = in.direction.reflect(hit.normal);
        out = Ray(hit.position, reflected + fuzz * sampler.get_sample());
        attenuation = albedo;
        return out.direction.dot(hit.normal) > 0;
    }
}