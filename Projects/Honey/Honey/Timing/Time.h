#pragma once

#include <Honey/Core/Engine.h>

namespace Honey {

	/**
	 * @brief Time related stuff.
	*/
	class Time {

	public:

		/**
		 * @brief Get time elapsed since start.
		 * @return Time since start.
		*/
		static Timestamp getTime() { return Engine::getTimer().getTime(); }

		/**
		 * @brief Get delta time.
		 * That is the time elapsed between this frame and the last one.
		 * @return Delta time.
		*/
		static Timestamp getDeltaTime() { return Engine::getTimer().getDeltaTime(); }

		/**
		 * @brief Get frame rate.
		 * @return Current frame rate.
		*/
		static Float getFrameRate() { return 1 / Engine::getTimer().getDeltaTime(); }

		/**
		 * @brief Get frame count since start.
		 * @return Frame count.
		*/
		static UInt getFrameCount() { return Engine::getTimer().getFrameCount(); }

	};
}
