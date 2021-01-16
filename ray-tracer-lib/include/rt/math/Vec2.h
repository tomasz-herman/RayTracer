#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H

#include <ostream>
#include <rt/utils/Printable.h>

namespace rt {
    struct Vec2 : public Printable {
        double x, y;

        Vec2();
        Vec2(double x, double y);

        void print(std::ostream& stream, int indent) const override;
    };
}

#endif //RAYTRACER_VEC2_H
