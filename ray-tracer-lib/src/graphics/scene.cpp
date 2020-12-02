#include "rt/graphics/scene.h"

namespace rt {
    scene::scene(const color3 &sky_color) : sky_color(sky_color) { }

    void scene::clear() {
        objects.clear();
    }

    void scene::add(const std::shared_ptr<hittable>& obj) {
        objects.push_back(obj);
    }

    bool scene::hit_test(const ray &ray, hit &hit, double from, double to) const {
        struct hit temp_hit;
        bool hit_anything = false;
        double closest = to;

        for (const auto& obj : objects) {
            if (obj->hit_test(ray, temp_hit, from, closest)) {
                hit_anything = true;
                closest = temp_hit.distance;
                hit = temp_hit;
            }
        }

        return hit_anything;
    }

    const color3& scene::get_sky_color() const {
        return sky_color;
    }

    void scene::set_sky_color(const color3 &skyColor) {
        sky_color = skyColor;
    }
}

