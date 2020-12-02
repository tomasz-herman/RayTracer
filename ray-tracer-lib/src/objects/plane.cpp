#include "rt/objects/plane.h"

namespace rt {
    plane::plane(std::shared_ptr<material> material_ptr, vec3 position, vec3 normal) : material_ptr(std::move(material_ptr)), position(position), normal(normal) { }

    bool plane::hit_test(const ray &ray, hit &hit, double from, double to) const {
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
}