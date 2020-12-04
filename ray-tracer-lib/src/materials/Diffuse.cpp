#include <rt/math/Utils.h>
#include "rt/materials/Diffuse.h"

namespace rt {
    Diffuse::Diffuse(Color3 albedo) : albedo(albedo) { }

    bool Diffuse::scatter(const Ray &in, const hit &hit, Color3 &attenuation, Ray &out) const {
        Vec3 dir = hit.normal + random_vec3_in_unit_sphere();
        out = Ray(hit.position, dir);
        attenuation = albedo;
        return true;
    }
}