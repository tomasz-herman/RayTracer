#include <rt/utils/StringUtils.h>
#include "rt/math/Vec2.h"

namespace rt {
    Vec2::Vec2() : x(0), y(0) { }
    Vec2::Vec2(double x, double y) : x(x), y(y) { }

    void Vec2::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"x\": " << x << "," << std::endl
               << two_spaces(indent + 1) << "\"y\": " << y << std::endl
               << two_spaces(indent) << "}";
    }
}