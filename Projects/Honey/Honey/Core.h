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