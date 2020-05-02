#pragma once

#include <cstddef>

#include "Timestamp.h"

namespace Honey {

	class Time {

	public:

		static Timestamp GetTime();
		static Timestamp GetDeltaTime();
		static float GetFrameRate();
		static std::size_t GetFrameCount();

	};
}