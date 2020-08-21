#pragma once

#include <Honey/Core/Engine.h>

namespace Honey {

	class Time {

	public:

		static Timestamp GetTime() { return Engine::GetTimer().GetTime(); }
		static Timestamp GetDeltaTime() { return Engine::GetTimer().GetDeltaTime(); }
		static float GetFrameRate() { return 1 / Engine::GetTimer().GetDeltaTime(); }
		static std::size_t GetFrameCount() { return Engine::GetTimer().GetFrameCount(); }

	};
}
