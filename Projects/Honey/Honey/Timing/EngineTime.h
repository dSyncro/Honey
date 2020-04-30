#pragma once

#include "Timestamp.h"

namespace Honey {

	class EngineTime {

	public:

		static Timestamp Time;
		static Timestamp DeltaTime;
		static unsigned int FrameCount;

	};
}
