#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <rt/objects/Hittable.h>
#include <vector>
#include <memory>

namespace rt {
    class Scene : Hittable {
    public:
        explicit Scene(const Color3& sky_color = Color3::LIGHTSKYBLUE());
        void clear();
        void add(const std::shared_ptr<Hittable>& obj);
        bool hit_test(const Ray &r, Hit &hit, double from, double to) const override;
        [[nodiscard]] const Color3& get_sky_color() const;
        void set_sky_color(const Color3 &skyColor);
    private:
        std::vector<std::shared_ptr<Hittable>> objects;
        Color3 sky_color;
    };
}



#endif //RAYTRACER_SCENE_H
