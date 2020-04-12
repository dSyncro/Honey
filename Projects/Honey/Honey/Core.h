#pragma once

#ifdef HNY_PLATFORM_WINDOWS
#	ifdef HNY_DYNAMIC_BUILD
#		ifdef HNY_BUILD_DLL
#			define HONEY_API __declspec(dllexport)
#		else
#			define HONEY_API __declspec(dllimport)
#		endif
#	else
#		define HONEY_API
#	endif
#else
#	error Honey only supports Windows!
#endif

#ifdef HNY_ENABLE_ASSERTS
#	define HNY_APP_ASSERT(x, ...) if (!x) { HNY_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#	define HNY_CORE_ASSERT(x, ...) if (!x) { HNY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
#	define HNY_APP_ASSERT(x, ...)
#	define HNY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) 1 << x

#define HNY_BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)