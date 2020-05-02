#pragma once

// OS Detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#	define HNY_PLATFORM_WINDOWS
#	if defined(_WIN64)
#		define HNY_PLATFORM_WINDOWS64
#	endif
#elif defined(__APPLE__) || defined(__MACH__)
#	define HNY_PLATFORM_APPLE
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR == 1
#		define HNY_PLATFORM_IPHONE_SIMULATOR
#		error "iPhone Simulator is not supported!"
#	elif TARGET_OS_IPHONE == 1
#		define HNY_PLATFORM_IOS
#		error "iOS is not supported!"
#	elif TARGET_OS_MAC == 1
#		define HNY_PLATFORM_MAC
#		error "MacOS is not supported!"
#	else
#		error "Unknown APPLE platform!"
#	endif
#elif defined(__ANDROID__)
#	define HNY_PLATFORM_ANDROID
#	error "Android is not supported!"
#elif defined(__linux__)
#	define HNY_PLATFORM_LINUX
#	error "Linux is not supported!"
#else
#	error "Unknown platform!"
#endif