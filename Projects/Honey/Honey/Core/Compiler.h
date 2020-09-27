/**
 * @file Compiler.h
 * @brief Information about the compiler used.
*/

#pragma once

/**
 * @def HNY_COMPILER_INTEL
 * @brief defined when using INTEL compiler.
*/

/**
 * @def HNY_COMPILER_MINGW
 * @brief defined when using MINGW compiler.
*/

/**
 * @def HNY_COMPILER_CLANG
 * @brief defined when using CLANG compiler.
*/

/**
 * @def HNY_COMPILER_GCC
 * @brief defined when using GCC compiler.
*/

/**
 * @def HNY_COMPILER_MSC
 * @brief defined when using MSC compiler.
*/

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
