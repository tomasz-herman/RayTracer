#include <rt/math/Vec3.h>
#include <cmath>

namespace rt {
    Vec3::Vec3() : x(0), y(0), z(0) {}
    Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3& Vec3::add(const Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3& Vec3::sub(const Vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3& Vec3::mul(double other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    Vec3& Vec3::div(double other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    Vec3 operator+(Vec3 left, const Vec3& right) {
        return left.add(right);
    }

    Vec3 operator-(Vec3 left, const Vec3& right) {
        return left.sub(right);
    }

    Vec3 operator*(Vec3 left, double right) {
        return left.mul(right);
    }

    Vec3 operator*(double left, Vec3 right) {
        return right * left;
    }

    Vec3 operator/(Vec3 left, double right) {
        return left.div(right);
    }

    Vec3 operator-(const Vec3 &vector) {
        return vector.negate();
    }

    Vec3 &Vec3::operator+=(const Vec3 &other) {
        return add(other);
    }

    Vec3 &Vec3::operator-=(const Vec3 &other) {
        return sub(other);
    }

    Vec3 &Vec3::operator*=(double other) {
        return mul(other);
    }

    Vec3 &Vec3::operator/=(double other) {
        return div(other);
    }

    bool Vec3::operator==(const Vec3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool Vec3::operator!=(const Vec3 &other) const {
        return !(*this == other);
    }

    Vec3 Vec3::negate() const {
        return Vec3(-x, -y, -z);
    }

    double Vec3::length() const {
        return sqrt(length_squared());
    }

    double Vec3::length_squared() const {
        return x * x + y * y + z * z;
    }

    Vec3 Vec3::normalized() const {
        return Vec3(*this) / length();
    }

    double Vec3::distance(const Vec3& other) const {
        return (*this - other).length();
    }

    double Vec3::dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 Vec3::cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    Vec3 Vec3::reflect(const Vec3& other) const {
        return *this - 2 * this->dot(other) * other;
    }

    std::ostream &operator<<(std::ostream &stream, const Vec3 &vector) {
        stream << "(x:" << vector.x << ", y:" << vector.y << ", z:" << vector.z << ")";
        return stream;
    }
}