// TODO: Refactor

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <Honey/Core/MemoryManagement.h>

namespace Honey {

	class Log {

	public:

		/**
		 * @brief Log level
		*/
		enum class Level {
			Trace = 0,
			Debug = 1,
			Info = 2,
			Warn = 3,
			Err = 4,
			Critical = 5,
			Off = 6
		};

		/**
		 * @brief Init Logging related stuff.
		*/
		static void init();

		/** @brief Get logger attached to core. */
		static Reference<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		/** @brief Get logger attached to app. */
		static Reference<spdlog::logger>& getAppLogger() { return s_AppLogger; }

	private:

		static Reference<spdlog::logger> s_CoreLogger;
		static Reference<spdlog::logger> s_AppLogger;

	};

}

#define HNY_CORE_TRACE(...)    ::Honey::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HNY_CORE_INFO(...)     ::Honey::Log::getCoreLogger()->info(__VA_ARGS__)
#define HNY_CORE_WARN(...)     ::Honey::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HNY_CORE_ERROR(...)    ::Honey::Log::getCoreLogger()->error(__VA_ARGS__)
#define HNY_CORE_CRITICAL(...) ::Honey::Log::getCoreLogger()->critical(__VA_ARGS__)

#define HNY_APP_TRACE(...)     ::Honey::Log::getAppLogger()->trace(__VA_ARGS__)
#define HNY_APP_INFO(...)      ::Honey::Log::getAppLogger()->info(__VA_ARGS__)
#define HNY_APP_WARN(...)      ::Honey::Log::getAppLogger()->warn(__VA_ARGS__)
#define HNY_APP_ERROR(...)     ::Honey::Log::getAppLogger()->error(__VA_ARGS__)
#define HNY_APP_CRITICAL(...)  ::Honey::Log::getAppLogger()->critical(__VA_ARGS__)
