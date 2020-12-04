#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <rt/math/Ray.h>

namespace rt {
    class Camera {
    public:
        [[nodiscard]] virtual Ray get_ray(double u, double v) const = 0;
        [[nodiscard]] virtual double get_aspect() const = 0;
    };
}

#endif //RAYTRACER_CAMERA_H
