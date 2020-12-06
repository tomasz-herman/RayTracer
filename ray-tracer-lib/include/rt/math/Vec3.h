#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <ostream>

namespace rt {
    struct Vec3 {
        double x, y, z;

        Vec3();
        Vec3(double x, double y, double z);

        Vec3& add(const Vec3& other);
        Vec3& sub(const Vec3& other);
        Vec3& mul(double other);
        Vec3& div(double other);

        friend Vec3 operator+(Vec3 left, const Vec3 &right);
        friend Vec3 operator-(Vec3 left, const Vec3 &right);
        friend Vec3 operator*(Vec3 left, double right);
        friend Vec3 operator*(double left, Vec3 right);
        friend Vec3 operator/(Vec3 left, double right);
        friend Vec3 operator-(const Vec3 &vector);

        Vec3& operator+=(const Vec3& other);
        Vec3& operator-=(const Vec3& other);
        Vec3& operator*=(double other);
        Vec3& operator/=(double other);

        bool operator==(const Vec3& other) const;
        bool operator!=(const Vec3& other) const;

        [[nodiscard]] double length() const;
        [[nodiscard]] double length_squared() const;
        [[nodiscard]] Vec3 normalized() const;
        [[nodiscard]] Vec3 negate() const;

        [[nodiscard]] double distance(const Vec3& other) const;
        [[nodiscard]] double dot(const Vec3& other) const;
        [[nodiscard]] Vec3 cross(const Vec3& other) const;
        [[nodiscard]] Vec3 reflect(const Vec3& other) const;

        friend std::ostream &operator<<(std::ostream &stream, const Vec3 &vector);
    };
}

#endif //RAYTRACER_VEC3_H
