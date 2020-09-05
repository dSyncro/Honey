#pragma once

#include <cstddef>

#include <Honey/Core/Assertion.h>

namespace Honey::Math {

	struct Span {

		Span() : Start(0), Length(0) {}
		Span(std::size_t start, std::size_t length) : Start(start), Length(length) {}

		std::size_t Start;
		std::size_t Length;

		std::size_t GetEnd() const noexcept { return Start + Length; }

		static Span FromBounds(std::size_t start, std::size_t end) 
		{ 
			HNY_CORE_ASSERT(start <= end, "End cannot be less than Start!"); 
			return Span(start, end - start); 
		}

	};

}
