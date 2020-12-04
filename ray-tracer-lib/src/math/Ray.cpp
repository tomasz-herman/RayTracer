#include "rt/math/Ray.h"

namespace rt {
    Ray::Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) { }

    Vec3 Ray::operator()(double t) const {
        return origin + t * direction;
    }
}


