#pragma once

#include "Core/Assertion.h"
#include "Core/Compiler.h"
#include "Core/Profiling.h"
#include "Core/MemoryTracking.h"
// #include "Core/DLLAutomation.h"

// Always inline
#if defined(HNY_COMPILER_GCC)
#	define HNY_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(HNY_COMPILER_MSC)
#	define HNY_ALWAYS_INLINE __forceinline
#else
#	define HNY_ALWAYS_INLINE inline
#endif

// Bitmasking
#define BIT(x) 1 << x

// Event Callback Binding
#define HNY_BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)