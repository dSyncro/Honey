#pragma once

#include "FunctionIdentification.h"
#include <Honey/Profiling/InstrumentationTimer.h>

#if defined(HNY_DEBUG)
#	define HNY_PROFILE 0
#endif

#if HNY_PROFILE == 1
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath) ::Honey::Instrumentor::Get().BeginSession(name, filepath)
#	define HNY_PROFILE_END_SESSION() ::Honey::Instrumentor::Get().EndSession()
#	define HNY_PROFILE_SCOPE(name) ::Honey::InstrumentationTimer timer##__LINE__(name)
#	define HNY_PROFILE_FUNCTION() HNY_PROFILE_SCOPE(HNY_FUNCTION_SIGNATURE)
#else
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath)
#	define HNY_PROFILE_END_SESSION()
#	define HNY_PROFILE_SCOPE(name)
#	define HNY_PROFILE_FUNCTION()
#endif