#include "rt/graphics/image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace rt {
    image::image(int width, int height) : width(width), height(height) {
        data = std::vector<std::vector<color3>>(height);
        for (auto &line : data) {
            line = std::vector<color3>(width);
        }
    }

    image::image(const image& img) : image(img.width, img.height) {
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                data[i][j] = img.data[i][j];
    }

    color3& image::operator()(int w, int h) {
        return data[h][w];
    }

    int image::get_width() const {
        return width;
    }

    int image::get_height() const {
        return height;
    }

    void image::write(const std::string& path) const {
        auto data_ptr = std::make_unique<uint8_t[]>(width * height * 3);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++) {
                color3 color = data[i][j];
                data_ptr[i * width * 3 + j * 3 + 0] = color.r * 255;
                data_ptr[i * width * 3 + j * 3 + 1] = color.g * 255;
                data_ptr[i * width * 3 + j * 3 + 2] = color.b * 255;
            }
        int result = stbi_write_png(path.c_str(), width, height, 3, data_ptr.get(), width * 3);
        if(!result) throw std::exception();
    }
}

