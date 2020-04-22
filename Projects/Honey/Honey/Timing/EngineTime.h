#pragma once

#include "Timestamp.h"

namespace Honey {

	struct EngineTime {

		static Timestamp Time;
		static Timestamp DeltaTime;
		static unsigned int FrameCount;

	};
}
