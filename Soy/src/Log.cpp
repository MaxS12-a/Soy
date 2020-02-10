#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> Log::coreLogger;

void Log::Init() {
	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Soy.log", true));

	sinks[0]->set_pattern("%^[%T]%l: %v%$");
	sinks[1]->set_pattern("[%T]%l: %v");

	coreLogger = std::make_shared<spdlog::logger>("SoyLog", begin(sinks), end(sinks));
	spdlog::register_logger(coreLogger);
	coreLogger->set_level(spdlog::level::trace);
	coreLogger->flush_on(spdlog::level::trace);
}