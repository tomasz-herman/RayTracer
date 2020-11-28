#include "rt/graphics/scene.h"

namespace rt {
    void scene::clear() {
        objects.clear();
    }

    void scene::add(const std::shared_ptr<hittable>& obj) {
        objects.push_back(obj);
    }

    bool scene::hit(const ray &r, struct hit &hit, double from, double to) const {
        struct hit temp_hit;
        bool hit_anything = false;
        double closest = to;

        for (const auto& obj : objects) {
            if (obj->hit(r, temp_hit, from, closest)) {
                hit_anything = true;
                closest = temp_hit.distance;
                hit = temp_hit;
            }
        }

        return hit_anything;
    }
}

