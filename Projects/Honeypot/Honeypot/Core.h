#pragma once

#include "../Libraries/Console.h"

#define HNYPT_NOTHING

#define HNYPT_TOSTRING(x) #x

#define HNYPT_CONCAT_IMPL(a, b) a##b
#define HNYPT_CONCAT(a, b) HNYPT_CONCAT_IMPL(a, b)

#if defined(__COUNTER__)
#	define HNYPT_SINGULAR(x) HNYPT_CONCAT(x, __COUNTER__)
#else
#	define HNYPT_SINGULAR(x) HNYPT_CONCAT(x, __LINE__)
#endif

#define HNYPT_LINE_ID(x) HNYPT_CONCAT(x, __LINE__)

// OS identification
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#	undef min // override standard definition
#	undef max // override standard definition
#	undef ERROR // override (really stupid) wingdi.h standard definition
#	undef DELETE // override (another really stupid) winnt.h standard definition
#	undef MessageBox // override winuser.h standard definition
#	undef MIN // override standard definition
#	undef MAX // override standard definition
#	undef CLAMP // override standard definition
#	undef Error
#	undef OK
#	undef near
#	undef far
#	undef CONNECT_DEFERRED // override from Windows SDK, clashes with Object enum
#	define HNYPT_PLATFORM_WINDOWS
#	if defined(_WIN64)
#		define HNYPT_PLATFORM_WINDOWS64
#	endif
#elif defined(__APPLE__) || defined(__MACH__)
#	define HNYPT_PLATFORM_APPLE
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR == 1
#		define HNYPT_PLATFORM_IPHONE_SIMULATOR
#		error "iPhone Simulator is not supported!"
#	elif TARGET_OS_IPHONE == 1
#		define HNYPT_PLATFORM_IOS
#		error "iOS is not supported!"
#	elif TARGET_OS_MAC == 1
#		define HNYPT_PLATFORM_MAC
#		error "MacOS is not supported!"
#	else
#		error "Unknown APPLE platform!"
#	endif
#elif defined(__ANDROID__)
#	define HNYPT_PLATFORM_ANDROID
#	error "Android is not supported!"
#elif defined(__linux__)
#	define HNYPT_PLATFORM_LINUX
#else
#	error "Unknown platform!"
#endif

// Breakpoint
#if defined(HNYPT_PLATFORM_WINDOWS)
#	define HNYPT_DEBUGBREAK() __debugbreak()
#elif defined(HNYPT_PLATFORM_LINUX)
#	include <signal.h>
#	define HNYPT_DEBUGBREAK() raise(SIGTRAP)
#else
#	error "Platform does not support breakpoint!"
#endif


#define HNYPT_ASSERT(x, ...) if (!(x)) { Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Assertion Failed: ", __VA_ARGS__); /*HNYPT_DEBUGBREAK();*/ }
