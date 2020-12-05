#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <rt/math/Vec3.h>
#include <rt/graphics/Image.h>
#include <rt/graphics/Renderer.h>
#include <rt/graphics/camera/PerspectiveCamera.h>
#include <rt/objects/Sphere.h>
#include <rt/materials/Diffuse.h>
#include <rt/objects/Plane.h>

void setup_logger();

int main() {
    setup_logger();

    rt::Renderer renderer(1280, 64, 10);
    rt::PerspectiveCamera camera(rt::Vec3(0, 0, 5), rt::Vec3(0, 0, 0), rt::Vec3(0, 1, 0), 60, 16.0 / 9.0);
    rt::Scene scene;

    scene.add(std::make_shared<rt::Sphere>(std::make_shared<rt::Diffuse>(rt::Color3::ORANGE()), rt::Vec3(0, 0, 0), 1));
    scene.add(std::make_shared<rt::Plane>(std::make_shared<rt::Diffuse>(rt::Color3::LAWNGREEN()), rt::Vec3(0, -1, 0)));

    rt::Image render = renderer.render(scene, camera);

    render.write("image.png");

    return 0;
}

void setup_logger() {
    spdlog::set_default_logger(spdlog::basic_logger_mt("ray_tracer", "log/ray_tracer.log"));
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    spdlog::flush_on(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
    spdlog::info("Logger set up and running. Log level is set to {}.", spdlog::level::to_string_view(spdlog::get_level()));
}
