/**
 * @file Assertion.h
 * @brief Assertion related stuff.
 */

#pragma once

#include "Breakpoint.h"
#include "Log.h"

// Assertion
#ifdef HNY_ENABLE_ASSERTS
#	define HNY_APP_ASSERT(x, ...) if (!(x)) { HNY_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); HNY_DEBUGBREAK(); }
#	define HNY_CORE_ASSERT(x, ...) if (!(x)) { HNY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HNY_DEBUGBREAK(); }
#else
#	define HNY_APP_ASSERT(x, ...)
#	define HNY_CORE_ASSERT(x, ...)
#endif
