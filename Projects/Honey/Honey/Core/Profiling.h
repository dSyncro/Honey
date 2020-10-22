/**
 * @file Profiling.h
 * @brief Enable (or disable) profiling tools.
 */

#pragma once

#include "Base.h"
#include "FunctionIdentification.h"
#include <Honey/Profiling/InstrumentationTimer.h>

/**
 * @def HNY_PROFILE
 * @brief Enable profiling.
*/

/**
 * @def HNY_PROFILE_BEGIN_SESSION(name, filepath)
 * @brief Begin profiling session.
*/

/**
 * @def HNY_PROFILE_END_SESSION()
 * @brief End current session.
*/

/**
 * @def HNY_PROFILE_SCOPE_ID(name, id)
 * @brief Profile scope with name and id.
 * @param name Scope name.
 * @param id Scope id.
*/

/**
 * @def HNY_PROFILE_SCOPE(name)
 * @brief Profile scope with name.
 * @param name Scope name.
*/

/**
 * @def HNY_PROFILE_FUNCTION()
 * @brief Profile function.
*/

#if defined(HNY_DEBUG)
#	define HNY_PROFILE 0
#endif

#if HNY_PROFILE == 1
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath) ::Honey::Instrumentor::Get().BeginSession(name, filepath)
#	define HNY_PROFILE_END_SESSION() ::Honey::Instrumentor::Get().EndSession()
#	define HNY_PROFILE_SCOPE_ID(name, id) ::Honey::InstrumentationTimer HNY_CONCAT(timer, id) (name)
#	define HNY_PROFILE_SCOPE(name) HNY_PROFILE_SCOPE_ID(name, __LINE__)
#	define HNY_PROFILE_FUNCTION() HNY_PROFILE_SCOPE(HNY_FUNCTION_NAME)
#else
#	define HNY_PROFILE_BEGIN_SESSION(name, filepath)
#	define HNY_PROFILE_END_SESSION()
#	define HNY_PROFILE_SCOPE_ID(name, line)
#	define HNY_PROFILE_SCOPE(name)
#	define HNY_PROFILE_FUNCTION()
#endif
