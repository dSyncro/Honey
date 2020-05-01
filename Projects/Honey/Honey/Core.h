#pragma once

#include <memory>

#define HNY_DEBUGBREAK() __debugbreak()

// DLL export macro
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

// Assertion
#ifdef HNY_ENABLE_ASSERTS
#	define HNY_APP_ASSERT(x, ...) if (!x) { HNY_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); HNY_DEBUGBREAK(); }
#	define HNY_CORE_ASSERT(x, ...) if (!x) { HNY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HNY_DEBUGBREAK(); }
#else
#	define HNY_APP_ASSERT(x, ...)
#	define HNY_CORE_ASSERT(x, ...)
#endif

// Bitmasking
#define BIT(x) 1 << x

// Event Callback Binding
#define HNY_BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)

namespace Honey {

	template<typename T>
	using Reference = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Reference<T> CreateReference(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}