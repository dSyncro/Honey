#pragma once

#include <cstddef>

#include "FunctionIdentification.h"

#if defined(HNY_DEBUG)
#	define HNY_MEMORY_TRACKING 0
#endif

#if HNY_MEMORY_TRACKING == 1

extern void* operator new(size_t size, char* file, std::size_t line, char* function);
extern void operator delete(void* ptr, char* file, std::size_t line, char* function);
extern void operator delete(void* ptr);

#	define NEW new((char*)__FILE__, __LINE__, HNY_FUNCTION_SIGNATURE)
#else
#	define NEW new
#endif