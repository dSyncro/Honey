/**
 * @file FunctionIdentification.h
 * @brief Identify function name and signature.
 */

#pragma once

#include "OS.h"

// Function Name
#if defined(HNY_PLATFORM_WINDOWS) //WINDOWS
#	define HNY_FUNCTION_NAME __FUNCTION__
#else //*NIX
#	define HNY_FUNCTION_NAME __func__ 
#endif

// Function Signature
#if defined(HNY_PLATFORM_WINDOWS)
#	define HNY_FUNCTION_SIGNATURE __FUNCSIG__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#	define HNY_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#	define HNY_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#	define HNY_FUNCTION_SIGNATURE __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#	define HNY_FUNCTION_SIGNATURE __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#	define HNY_FUNCTION_SIGNATURE __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#	define HNY_FUNCTION_SIGNATURE __func__
#else
#	define HNY_FUNCTION_SIGNATURE "HNY_FUNCTION_SIGNATURE unknown!"
#endif