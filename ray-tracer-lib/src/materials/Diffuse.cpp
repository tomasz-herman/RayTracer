#include <rt/math/Utils.h>
#include <rt/utils/StringUtils.h>
#include "rt/materials/Diffuse.h"

namespace rt {
    Diffuse::Diffuse(Color3 albedo, Sampler<Vec3> sampler) : albedo(albedo), sampler(std::move(sampler)) {}

    bool Diffuse::scatter(const Ray &in, const Hit &hit, Color3 &attenuation, Ray &out) {
        Vec3 dir = hit.normal + sampler.get_sample();
        out = Ray(hit.position, dir);
        attenuation = albedo;
        return true;
    }

    void Diffuse::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"type\": " << "\"diffuse\"," << std::endl
               << two_spaces(indent + 1) << "\"albedo\": " << std::endl;
        albedo.print(stream, indent + 2);
        stream << std::endl
               << two_spaces(indent) << "}";
    }
}