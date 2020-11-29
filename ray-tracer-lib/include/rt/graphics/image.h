#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <memory>
#include <rt/math/color3.h>
#include <vector>
#include <ostream>

namespace rt {
    class image {
        int width, height;
        std::vector<std::vector<color3>> data;

    public:
        image(int width, int height);
        image(const image& img);

        color3& operator()(int w, int h);

        [[nodiscard]] int get_width() const;
        [[nodiscard]] int get_height() const;

        void write(const std::string& path) const;
    };
}


#endif //RAYTRACER_IMAGE_H
