#include "rt/math/Vec2.h"

namespace rt {
    Vec2::Vec2() : x(0), y(0) { }
    Vec2::Vec2(double x, double y) : x(x), y(y) { }

    std::ostream &operator<<(std::ostream &stream, const Vec2 &vector) {
        stream << "(x:" << vector.x << ", y:" << vector.y << ")";
        return stream;
    }
}