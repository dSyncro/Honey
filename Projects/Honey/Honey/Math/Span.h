#pragma once

#include <cstddef>

#include <Honey/Core/Assertion.h>

namespace Honey::Math {

	/**
	 * @brief The length of something from one end to the other.
	*/
	struct Span {

		/**
		 * @brief Construct a default Span.
		*/
		Span() : start(0), length(0) {}

		/**
		 * @brief Construct a span.
		 * @param start Span startpoint.
		 * @param length Span length.
		*/
		Span(UInt start, UInt length) : start(start), length(length) {}

		UInt start; /** @brief Span start. */
		UInt length; /** @brief Span length. */

		/** @brief Span end. */
		UInt end() const noexcept { return start + length; }

		/**
		 * @brief Create span from startpoint and endpoint.
		 * @param start Startpoint.
		 * @param end Endpoint.
		 * @return A new span with specified bounds.
		*/
		static Span FromBounds(UInt start, UInt end) 
		{ 
			HNY_CORE_ASSERT(start <= end, "End cannot be less than Start!"); 
			return Span(start, end - start); 
		}

	};

}
