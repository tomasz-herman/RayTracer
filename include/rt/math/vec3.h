#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <ostream>

namespace rt {
    struct vec3 {
        double x, y, z;

        vec3();
        vec3(double x, double y, double z);

        vec3& add(const vec3& other);
        vec3& sub(const vec3& other);
        vec3& mul(double other);
        vec3& div(double other);

        friend vec3 operator+(vec3 left, const vec3 &right);
        friend vec3 operator-(vec3 left, const vec3 &right);
        friend vec3 operator*(vec3 left, double right);
        friend vec3 operator/(vec3 left, double right);
        friend vec3 operator-(const vec3 &vector);

        double length() const;
        double length_squared() const;
        vec3 normalize() const;
        vec3 negate() const;

        friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
    };
}

#endif //RAYTRACER_VEC3_H
