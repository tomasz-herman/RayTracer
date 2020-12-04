#ifndef RAYTRACER_PERSPECTIVECAMERA_H
#define RAYTRACER_PERSPECTIVECAMERA_H

#include "Camera.h"

namespace rt {
    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(Vec3 position, Vec3 at, Vec3 up, double fov, double aspect);

        [[nodiscard]] Ray get_ray(double u, double v) const override;
        [[nodiscard]] double get_aspect() const override;
    private:
        Vec3 position;
        Vec3 lower_left;
        Vec3 horizontal;
        Vec3 vertical;
        double aspect;
    };
}



#endif //RAYTRACER_PERSPECTIVECAMERA_H
