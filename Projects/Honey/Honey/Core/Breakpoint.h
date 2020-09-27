/**
 * @file Breakpoint.h
 * @brief Use breakpoints programmatically.
*/

#pragma once

#include "OS.h"

/* 
 * @def HNY_DEBUGBREAK()
 * @brief IDE-independant breakpoint.
 * Only valid in Debug builds.
*/

// Breakpoint
#if defined(HNY_DEBUG)
#	if defined(HNY_PLATFORM_WINDOWS)
#		define HNY_DEBUGBREAK() __debugbreak()
#	elif defined(HNY_PLATFORM_LINUX)
#		include <signal.h>
#		define HNY_DEBUGBREAK() raise(SIGTRAP)
#	else
#		error "Platform does not support breakpoint!"
#	endif
#	define HNY_ENABLE_ASSERTS
#else
#	define HNY_DEBUGBREAK()
#endif
