#pragma once

#include "Timestamp.h"

namespace Honey {

	struct Time {

		static Timestamp GetTime();
		static Timestamp GetDeltaTime();
		static float GetFrameRate();
		static unsigned int GetFrameCount();

	};

}