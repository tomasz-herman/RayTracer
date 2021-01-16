#include <cmath>
#include <rt/utils/StringUtils.h>
#include "rt/objects/Sphere.h"

namespace rt {
    Sphere::Sphere(std::shared_ptr<Material> material_ptr, Vec3 position, double radius) : material_ptr(
            std::move(material_ptr)), position(position), radius(radius) {}

    Sphere::Sphere(std::shared_ptr<Material> material_ptr, double x, double y, double z, double radius) : material_ptr(
            std::move(material_ptr)), position(Vec3(x, y, z)), radius(radius) {}

    bool Sphere::hit_test(const Ray &ray, Hit &hit, double from, double to) const {
        Vec3 oc = ray.origin - position;
        double a = ray.direction.length_squared();
        double half_b = oc.dot(ray.direction);
        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);

        double root = (-half_b - sqrtd) / a;
        if (root < from || to < root) {
            root = (-half_b + sqrtd) / a;
            if (root < from || to < root)
                return false;
        }

        hit.distance = root;
        hit.position = ray(hit.distance);
        hit.material_ptr = material_ptr;
        hit.normal = (hit.position - position) / radius;

        return true;
    }

    void Sphere::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"type\": " << "\"sphere\"," << std::endl
               << two_spaces(indent + 1) << "\"position\": " << std::endl;
        position.print(stream, indent + 2);
        stream << "," << std::endl
               << two_spaces(indent + 1) << "\"radius\": " << radius << "," << std::endl
               << two_spaces(indent + 1) << "\"material\": " << std::endl;
        (*material_ptr).print(stream, indent + 2);
        stream << std::endl
               << two_spaces(indent) << "}";
    }
}