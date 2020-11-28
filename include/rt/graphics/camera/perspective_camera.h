#ifndef RAYTRACER_PERSPECTIVE_CAMERA_H
#define RAYTRACER_PERSPECTIVE_CAMERA_H

#include "camera.h"

namespace rt {
    class perspective_camera : camera {
    public:
        perspective_camera(vec3 position, vec3 at, vec3 up, double fov, double aspect);

        [[nodiscard]] ray get_ray(double u, double v) const override;
    private:
        vec3 position;
        vec3 lower_left;
        vec3 horizontal;
        vec3 vertical;
    };
}



#endif //RAYTRACER_PERSPECTIVE_CAMERA_H
