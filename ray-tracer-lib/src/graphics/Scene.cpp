#include <numeric>
#include <rt/math/Utils.h>
#include <rt/utils/StringUtils.h>
#include "rt/graphics/Scene.h"
#include "algorithm"

namespace rt {
    Scene::Scene(const Color3 &sky_color) : sky_color(sky_color) {}

    void Scene::clear() {
        objects.clear();
    }

    void Scene::add(const std::shared_ptr<Hittable> &obj) {
        objects.push_back(obj);
    }

    bool Scene::hit_test(const Ray &ray, Hit &hit, double from, double to) const {
        Hit temp_hit;
        bool hit_anything = false;
        double closest = to;

        for (const auto &obj : objects) {
            if (obj->hit_test(ray, temp_hit, from, closest)) {
                hit_anything = true;
                closest = temp_hit.distance;
                hit = temp_hit;
                *obj;
            }
        }

        return hit_anything;
    }

    const Color3 &Scene::get_sky_color() const {
        return sky_color;
    }

    void Scene::set_sky_color(const Color3 &skyColor) {
        sky_color = skyColor;
    }

    void Scene::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"type\": " << "\"scene\"," << std::endl
               << two_spaces(indent + 1) << "\"sky_color\": " << std::endl;
        sky_color.print(stream, indent + 2);
        stream << "," << std::endl
               << two_spaces(indent + 1) << "\"objects\": [" << std::endl;
        if(objects.size() > 1){
            for (auto iter = objects.begin(); iter != objects.end() - 1; iter++) {
                (**iter).print(stream, indent + 2);
                stream << "," << std::endl;
            }
        }
        if(!objects.empty()) {
            (**(objects.end() - 1)).print(stream, indent + 2);
        }
        stream << std::endl
               << two_spaces(indent + 1) << "]" << std::endl
               << two_spaces(indent) << "}";
    }
}

