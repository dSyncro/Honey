#pragma once

#include <Honey/Core/Engine.h>

namespace Honey {

	class Time {

	public:

		static Timestamp GetTime() { return Engine::getTimer().getTime(); }
		static Timestamp GetDeltaTime() { return Engine::getTimer().getDeltaTime(); }
		static float GetFrameRate() { return 1 / Engine::getTimer().getDeltaTime(); }
		static std::size_t GetFrameCount() { return Engine::getTimer().getFrameCount(); }

	};
}
