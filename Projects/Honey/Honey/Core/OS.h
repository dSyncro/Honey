#pragma once

// OS Detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#	define HNY_PLATFORM_WINDOWS
#	include <Windows.h>
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
//#	error "Linux is not supported!"
#else
#	error "Unknown platform!"
#endif

#if defined(HNY_PLATFORM_WINDOWS) || defined(HNY_PLATFORM_LINUX)
#	define HNY_PLATFORM_GLFW
#endif