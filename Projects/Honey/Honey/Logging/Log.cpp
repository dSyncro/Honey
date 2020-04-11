#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

using namespace Honey;

std::shared_ptr<spdlog::logger> Log::_coreLogger;
std::shared_ptr<spdlog::logger> Log::_appLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	_coreLogger = spdlog::stdout_color_mt("HONEY");
	_coreLogger->set_level(spdlog::level::level_enum::trace);

	_appLogger = spdlog::stdout_color_mt("APPLICATION");
	_appLogger->set_level(spdlog::level::level_enum::trace);
}