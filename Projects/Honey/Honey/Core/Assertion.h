/**
 * @file Assertion.h
 * @brief Assertion related stuff.
*/

#pragma once

#include <filesystem>

#include "Base.h"
#include "Breakpoint.h"
#include "Log.h"

/**
 * @def HNY_APP_ASSERT(x, ...)
 * @brief Assert throwing an APP Error in case of failure.
*/

/**
 * @def HNY_CORE_ASSERT(x, ...)
 * @brief Assert throwing a Core Error in case of failure.
*/

// Assertion
#ifdef HNY_ENABLE_ASSERTS
#	define HNY_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HNY##type##ERROR(msg, __VA_ARGS__); HNY_DEBUGBREAK(); } }
#	define HNY_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HNY_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#	define HNY_INTERNAL_ASSERT_NO_MSG(type, check) HNY_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}: {2}", HNY_STRINGIFY(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
#	define HNY_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#	define HNY_INTERNAL_ASSERT_GET_MACRO(...) HNY_EXPAND( HNY_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HNY_INTERNAL_ASSERT_WITH_MSG, HNY_INTERNAL_ASSERT_NO_MSG) )
#	define HNY_APP_ASSERT(...) HNY_EXPAND( HNY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_APP_, __VA_ARGS__) )
#	define HNY_CORE_ASSERT(...) HNY_EXPAND( HNY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#	define HNY_APP_ASSERT(x, ...)
#	define HNY_CORE_ASSERT(x, ...)
#endif
