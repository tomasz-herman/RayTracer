#include <ray-tracer-lib/math/vec3.h>

namespace rt {
    vec3::vec3() : x(0), y(0), z(0) {}
    vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    inline vec3& vec3::add(const vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline vec3& vec3::sub(const vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline vec3& vec3::mul(double other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    inline vec3& vec3::div(double other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    inline vec3 operator+(vec3 left, const vec3& right) {
        return left.add(right);
    }

    inline vec3 operator-(vec3 left, const vec3& right) {
        return left.sub(right);
    }

    inline vec3 operator*(vec3 left, double right) {
        return left.mul(right);
    }

    inline vec3 operator/(vec3 left, double right) {
        return left.div(right);
    }

    inline vec3 operator-(const vec3 &vector) {
        return vector.negate();
    }

    std::ostream &operator<<(std::ostream &stream, const vec3 &vector) {
        stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return stream;
    }
}