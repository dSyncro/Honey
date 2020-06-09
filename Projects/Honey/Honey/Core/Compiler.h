/**
 * @file Compiler.h
 * @brief Information about the compiler used.
 */

#pragma once

#if defined(__INTEL_COMPILER)
#	define HNY_COMPILER_INTEL
#elif defined(__MINGW32__) || defined(__MINGW64__)
#	define HNY_COMPILER_MINGW
#elif defined(__clang__)
#	define HNY_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#	define HNY_COMPILER_GCC
#elif defined(_MSC_VER)
#	define HNY_COMPILER_MSC
#endif