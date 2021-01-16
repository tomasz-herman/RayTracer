#include <rt/utils/StringUtils.h>
#include "rt/materials/Reflective.h"

namespace rt {

    Reflective::Reflective(Color3 albedo, double fuzz, Sampler<Vec3> sampler) : albedo(albedo), fuzz(fuzz),
                                                                                sampler(std::move(sampler)) {}

    bool Reflective::scatter(const Ray &in, const Hit &hit, Color3 &attenuation, Ray &out) {
        Vec3 reflected = in.direction.reflect(hit.normal);
        out = Ray(hit.position, reflected + fuzz * sampler.get_sample());
        attenuation = albedo;
        return out.direction.dot(hit.normal) > 0;
    }

    void Reflective::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"type\": " << "\"reflective\"," << std::endl
               << two_spaces(indent + 1) << "\"albedo\": " << std::endl;
        albedo.print(stream, indent + 2);
        stream << "," << std::endl
               << two_spaces(indent + 1) << "\"fuzz\": " << fuzz << std::endl
               << two_spaces(indent) << "}";
    }
}