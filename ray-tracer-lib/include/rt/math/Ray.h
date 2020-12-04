#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vec3.h"

namespace rt {
    struct Ray {
        Vec3 origin, direction;

        Ray(Vec3 origin, Vec3 direction);

        Vec3 operator()(double t) const;
    };
}


#endif //RAYTRACER_RAY_H
