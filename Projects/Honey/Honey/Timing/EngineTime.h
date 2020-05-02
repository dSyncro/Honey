#pragma once

#include <cstddef>

#include "Timestamp.h"

namespace Honey {

	class EngineTime {

	public:

		static Timestamp GetTime() { return Time; }
		static Timestamp GetDeltaTime() { return DeltaTime; }
		static std::size_t GetFrameCount() { return FrameCount; }

		static void SetTime(Timestamp time) { Time = time; }
		static void SetDeltaTime(Timestamp deltaTime) { DeltaTime = deltaTime; }
		static void SetFrameCount(std::size_t frameCount) { FrameCount = frameCount; }

	private:

		static Timestamp Time;
		static Timestamp DeltaTime;
		static std::size_t FrameCount;

	};
}
