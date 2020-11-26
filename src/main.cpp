#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

void setup_logger();

int main() {
    setup_logger();
    return 0;
}

void setup_logger() {
    spdlog::set_default_logger(spdlog::basic_logger_mt("model_loader", "log/ray_tracer.log"));
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    spdlog::flush_on(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
    spdlog::info("Logger set up and running. Log level is set to {}.", spdlog::level::to_string_view(spdlog::get_level()));
}
