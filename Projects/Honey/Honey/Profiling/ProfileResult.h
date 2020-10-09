#pragma once

#include <chrono>
#include <string>
#include <thread>

#include <Honey/Core/TypeTraits.h>

namespace Honey {

	/**
	 * @brief Microseconds in floating point format.
	*/
	using FloatingPointMicroseconds = std::chrono::duration<Double, std::micro>;

	/**
	 * @brief Profiling result.
	*/
	struct ProfileResult
	{
		/** @brief Profile name */
		std::string name;

		/** @brief Start timepoint */
		FloatingPointMicroseconds start;

		/** @brief Elapsed time. */
		std::chrono::microseconds elapsedTime;

		/** @brief Thread ID. */
		std::thread::id threadID;
	};

}
