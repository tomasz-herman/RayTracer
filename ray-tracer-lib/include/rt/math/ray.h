#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

namespace rt {
    struct ray {
        vec3 origin, direction;

        ray(vec3 origin, vec3 direction);

        vec3 operator()(double t) const;
    };
}


#endif //RAYTRACER_RAY_H
