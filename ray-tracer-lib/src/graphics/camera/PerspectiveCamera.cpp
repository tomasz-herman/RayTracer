#include <cmath>
#include <rt/math/Utils.h>
#include "rt/graphics/camera/PerspectiveCamera.h"

namespace rt {
    PerspectiveCamera::PerspectiveCamera(Vec3 position, Vec3 at, Vec3 up, double fov, double aspect) : position(position), aspect(aspect) {
        double width = 2.0 * tan(deg_to_rad(fov) / 2.0);
        double height = width / aspect;

        auto w = (position - at).normalized();
        auto u = up.cross(w).normalized();
        auto v = w.cross(u);

        horizontal = width * u;
        vertical = height * v;
        lower_left = position - horizontal / 2 - vertical / 2 - w;
    }

    Ray PerspectiveCamera::get_ray(double u, double v) const {
        return Ray(position, lower_left + u * horizontal + v * vertical - position);
    }

    double PerspectiveCamera::get_aspect() const {
        return aspect;
    }
}

