/**
 * @file OS.h
 * @brief OS related stuff.
*/

#pragma once

/**
 * @def HNY_PLATFORM_WINDOWS
 * @brief Defined if building on a Windows Machine.
*/

/**
 * @def HNY_PLATFORM_WINDOWS64
 * @brief Defined if building on a 64-bit Windows Machine.
*/

/**
 * @def HNY_PLATFORM_APPLE
 * @brief Defined if building on an Apple Machine.
*/

/**
 * @def HNY_PLATFORM_IPHONE_SIMULATOR
 * @brief Defined if building on an iPhone simulator.
*/

/**
 * @def HNY_PLATFORM_IOS
 * @brief Defined if building on an IOS Machine.
*/

/**
 * @def HNY_PLATFORM_MAC
 * @brief Defined if building on a MacOS Machine.
*/

/**
 * @def HNY_PLATFORM_ANDROID
 * @brief Defined if building on an Android Machine.
*/

/**
 * @def HNY_PLATFORM_LINUX
 * @brief Defined if building on a Linux Machine.
*/

/**
 * @def HNY_PLATFORM_GLFW
 * @brief Defined if platform utilises GLFW.
*/

// OS Detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#	define HNY_PLATFORM_WINDOWS
#	define HNY_PREFER_GLFW 1
#	include <Honey/Platform/Windows/WindowsHeader.h>
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
#else
#	error "Unknown platform!"
#endif

#if (defined(HNY_PLATFORM_WINDOWS) && HNY_PREFER_GLFW) || defined(HNY_PLATFORM_LINUX)
#	define HNY_PLATFORM_GLFW
#endif
