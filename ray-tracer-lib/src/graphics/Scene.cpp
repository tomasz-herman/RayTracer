#include "rt/graphics/Scene.h"

namespace rt {
    Scene::Scene(const Color3 &sky_color) : sky_color(sky_color) { }

    void Scene::clear() {
        objects.clear();
    }

    void Scene::add(const std::shared_ptr<Hittable>& obj) {
        objects.push_back(obj);
    }

    bool Scene::hit_test(const Ray &ray, hit &hit, double from, double to) const {
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

    const Color3& Scene::get_sky_color() const {
        return sky_color;
    }

    void Scene::set_sky_color(const Color3 &skyColor) {
        sky_color = skyColor;
    }
}

