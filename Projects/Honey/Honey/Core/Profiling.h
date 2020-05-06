#pragma once

#include "FunctionIdentification.h"
#include <Honey/Profiling/InstrumentationTimer.h>

#if defined(HNY_DEBUG)
#	define HNY_PROFILE 0
#endif

#define CONCAT(a, b) a##b

#if HNY_PROFILE == 1
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath) ::Honey::Instrumentor::Get().BeginSession(name, filepath)
#	define HNY_PROFILE_END_SESSION() ::Honey::Instrumentor::Get().EndSession()
#	define HNY_PROFILE_SCOPE_ID(name, line) ::Honey::InstrumentationTimer CONCAT(timer, line) (name)
#	define HNY_PROFILE_SCOPE(name) HNY_PROFILE_SCOPE_ID(name, __LINE__)
#	define HNY_PROFILE_FUNCTION() HNY_PROFILE_SCOPE(HNY_FUNCTION_NAME)
#else
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath)
#	define HNY_PROFILE_END_SESSION()
#	define HNY_PROFILE_SCOPE_ID(name, line)
#	define HNY_PROFILE_SCOPE(name)
#	define HNY_PROFILE_FUNCTION()
#endif