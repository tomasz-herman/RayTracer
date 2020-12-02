#include <rt/math/utils.h>
#include "rt/materials/diffuse.h"

namespace rt {
    diffuse::diffuse(color3 albedo) : albedo(albedo) { }

    bool diffuse::scatter(const ray &in, const hit &hit, color3 &attenuation, ray &out) const {
        vec3 dir = hit.normal + random_vec3_in_unit_sphere();
        out = ray(hit.position, dir);
        attenuation = albedo;
        return true;
    }
}