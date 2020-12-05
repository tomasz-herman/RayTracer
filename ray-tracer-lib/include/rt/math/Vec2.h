#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H

#include <ostream>

namespace rt {
    struct Vec2 {
        double x, y;

        Vec2();
        Vec2(double x, double y);

        friend std::ostream &operator<<(std::ostream &stream, const Vec2 &vector);
    };
}

#endif //RAYTRACER_VEC2_H
