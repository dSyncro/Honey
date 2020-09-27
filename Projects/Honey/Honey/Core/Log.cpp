#include "Log.h"

using namespace Honey;

Reference<spdlog::logger> Log::s_CoreLogger;
Reference<spdlog::logger> Log::s_AppLogger;

void Log::init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_CoreLogger = spdlog::stdout_color_mt("HONEY");
	s_CoreLogger->set_level(spdlog::level::level_enum::trace);

	s_AppLogger = spdlog::stdout_color_mt("APPLICATION");
	s_AppLogger->set_level(spdlog::level::level_enum::trace);
}
