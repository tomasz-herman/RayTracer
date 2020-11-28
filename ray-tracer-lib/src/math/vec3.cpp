#include <rt/math/vec3.h>
#include <cmath>

namespace rt {
    vec3::vec3() : x(0), y(0), z(0) {}
    vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    vec3& vec3::add(const vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec3& vec3::sub(const vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec3& vec3::mul(double other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    vec3& vec3::div(double other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    vec3 operator+(vec3 left, const vec3& right) {
        return left.add(right);
    }

    vec3 operator-(vec3 left, const vec3& right) {
        return left.sub(right);
    }

    vec3 operator*(vec3 left, double right) {
        return left.mul(right);
    }

    vec3 operator*(double left, vec3 right) {
        return right * left;
    }

    vec3 operator/(vec3 left, double right) {
        return left.div(right);
    }

    vec3 operator-(const vec3 &vector) {
        return vector.negate();
    }

    vec3 &vec3::operator+=(const vec3 &other) {
        return add(other);
    }

    vec3 &vec3::operator-=(const vec3 &other) {
        return sub(other);
    }

    vec3 &vec3::operator*=(double other) {
        return mul(other);
    }

    vec3 &vec3::operator/=(double other) {
        return div(other);
    }

    bool vec3::operator==(const vec3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool vec3::operator!=(const vec3 &other) const {
        return !(*this == other);
    }

    vec3 vec3::negate() const {
        return vec3(-x, -y, -z);
    }

    double vec3::length() const {
        return sqrt(length_squared());
    }

    double vec3::length_squared() const {
        return x * x + y * y + z * z;
    }

    vec3 vec3::normalized() const {
        return vec3(*this) / length();
    }

    double vec3::distance(const vec3& other) const {
        return (*this - other).length();
    }

    double vec3::dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3 vec3::cross(const vec3& other) const {
        return vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    std::ostream &operator<<(std::ostream &stream, const vec3 &vector) {
        stream << "(x:" << vector.x << ", y:" << vector.y << ", z:" << vector.z << ")";
        return stream;
    }
}