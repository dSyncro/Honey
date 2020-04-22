#pragma once

#include <Honey/Core.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Honey {

	class HONEY_API Log {

	public:

		static void Init();

		inline static Reference<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Reference<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

	private:

		static Reference<spdlog::logger> s_CoreLogger;
		static Reference<spdlog::logger> s_AppLogger;

	};

}

#define HNY_CORE_TRACE(...) ::Honey::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define HNY_CORE_INFO(...)  ::Honey::Log::GetCoreLogger()->info(__VA_ARGS__);
#define HNY_CORE_WARN(...)  ::Honey::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define HNY_CORE_ERROR(...) ::Honey::Log::GetCoreLogger()->error(__VA_ARGS__);
#define HNY_CORE_CRITICAL(...) ::Honey::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define HNY_APP_TRACE(...) ::Honey::Log::GetAppLogger()->trace(__VA_ARGS__);
#define HNY_APP_INFO(...)  ::Honey::Log::GetAppLogger()->info(__VA_ARGS__);
#define HNY_APP_WARN(...)  ::Honey::Log::GetAppLogger()->warn(__VA_ARGS__);
#define HNY_APP_ERROR(...) ::Honey::Log::GetAppLogger()->error(__VA_ARGS__);
#define HNY_APP_CRITICAL(...) ::Honey::Log::GetAppLogger()->critical(__VA_ARGS__);