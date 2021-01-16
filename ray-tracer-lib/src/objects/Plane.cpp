#include <rt/math/Utils.h>
#include <rt/utils/StringUtils.h>
#include "rt/objects/Plane.h"

namespace rt {
    Plane::Plane(std::shared_ptr<Material> material_ptr, Vec3 position, Vec3 normal) : material_ptr(
            std::move(material_ptr)), position(position), normal(normal) {}

    bool Plane::hit_test(const Ray &ray, Hit &hit, double from, double to) const {
        double t = (position - ray.origin).dot(normal) / ray.direction.dot(normal);

        if (t < from || to < t) {
            return false;
        }

        hit.distance = t;
        hit.position = ray(hit.distance);
        hit.material_ptr = material_ptr;
        hit.normal = normal;

        return true;
    }

    void Plane::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"type\": " << "\"plane\"," << std::endl
               << two_spaces(indent + 1) << "\"position\": " << std::endl;
        position.print(stream, indent + 2);
        stream << "," << std::endl
               << two_spaces(indent + 1) << "\"normal\": " << std::endl;
        normal.print(stream, indent + 2);
        stream << "," << std::endl
               << two_spaces(indent + 1) << "\"material\": " << std::endl;
        (*material_ptr).print(stream, indent + 2);
        stream << std::endl
               << two_spaces(indent) << "}";
    }
}