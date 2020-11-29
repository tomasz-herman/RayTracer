#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <rt/objects/hittable.h>
#include <vector>
#include <memory>

namespace rt {
    class scene : hittable {
    public:
        void clear();
        void add(const std::shared_ptr<hittable>& obj);
        bool hit_test(const ray &r, hit &hit, double from, double to) const override;
    private:
        std::vector<std::shared_ptr<hittable>> objects;
    };
}



#endif //RAYTRACER_SCENE_H
