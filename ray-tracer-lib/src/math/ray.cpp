#include "rt/math/ray.h"

namespace rt {
    ray::ray(vec3 origin, vec3 direction) : origin(origin), direction(direction) { }

    vec3 ray::operator()(double t) const {
        return origin + t * direction;
    }
}


