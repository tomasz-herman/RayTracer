#ifndef RAYTRACER_STRINGUTILS_H
#define RAYTRACER_STRINGUTILS_H

#include "string"

namespace rt {
    inline static std::string two_spaces(int indent) {
        return std::string(indent * 2, ' ');
    }

    inline static std::string four_spaces(int indent) {
        return std::string(indent * 4, ' ');
    }

    inline static std::string tabs(int indent) {
        return std::string(indent, '\t');
    }
}

#endif //RAYTRACER_STRINGUTILS_H
