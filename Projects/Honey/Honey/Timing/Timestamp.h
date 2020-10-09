#pragma once

#include <Honey/Core/TypeTraits.h>

namespace Honey {

	/**
	 * @brief A timestamp represents a point in time.
	*/
	class Timestamp {

	public:

		/**
		 * @brief Construct Timestamp.
		 * @param time Time point.
		*/
		Timestamp(Float time = 0.0f) : _time(time) {}

		/**
		 * @brief Implicitly convertible to float.
		*/
		operator Float() const { return _time; }

		/**
		 * @brief Add a certain amount of time to timestamp.
		 * @param amount Time amount.
		 * @return The timestamp.
		*/
		Timestamp& operator +=(Float amount) { return _time += amount, *this; }

		/**
		 * @brief Subtract a certain amount of time from timestamp.
		 * @param amount Time amount.
		 * @return The timestamp.
		*/
		Timestamp& operator -=(Float amount) { return _time -= amount, *this; }

		/**
		 * @brief Get timestamp seconds.
		 * @return Seconds represented by timestamp.
		*/
		Float GetSeconds() const { return _time; }

		/**
		 * @brief Get timestamp milliseconds.
		 * @return Milliseconds represented by timestamp.
		*/
		Float GetMilliseconds() const { return _time * 1000.0f; }

	private:

		Float _time;
	};

}
