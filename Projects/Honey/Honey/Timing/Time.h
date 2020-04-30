#pragma once

#include "Timestamp.h"

namespace Honey {

	class Time {

	public:

		static Timestamp GetTime();
		static Timestamp GetDeltaTime();
		static float GetFrameRate();
		static unsigned int GetFrameCount();

	};
}