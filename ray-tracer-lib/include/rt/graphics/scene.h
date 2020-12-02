#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <rt/objects/hittable.h>
#include <vector>
#include <memory>

namespace rt {
    class scene : hittable {
    public:
        explicit scene(const color3& sky_color = color3::SKYBLUE());
        void clear();
        void add(const std::shared_ptr<hittable>& obj);
        bool hit_test(const ray &r, hit &hit, double from, double to) const override;
        [[nodiscard]] const color3& get_sky_color() const;
        void set_sky_color(const color3 &skyColor);
    private:
        std::vector<std::shared_ptr<hittable>> objects;
        color3 sky_color;
    };
}



#endif //RAYTRACER_SCENE_H
