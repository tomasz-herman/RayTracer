#include <cmath>
#include <rt/math/utils.h>
#include "rt/graphics/camera/perspective_camera.h"

namespace rt {
    perspective_camera::perspective_camera(vec3 position, vec3 at, vec3 up, double fov, double aspect) : position(position), aspect(aspect) {
        double width = 2.0 * tan(deg_to_rad(fov) / 2.0);
        double height = width / aspect;

        auto w = (position - at).normalized();
        auto u = up.cross(w).normalized();
        auto v = w.cross(u);

        horizontal = width * u;
        vertical = height * v;
        lower_left = position - horizontal / 2 - vertical / 2 - w;
    }

    ray perspective_camera::get_ray(double u, double v) const {
        return ray(position, lower_left + u * horizontal + v * vertical - position);
    }

    double perspective_camera::get_aspect() const {
        return aspect;
    }
}

