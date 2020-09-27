/**
 * @file Engine.h
*/

#pragma once

#include <chrono>

#include <Honey/Timing/Timestamp.h>

namespace Honey {

	/**
	 * @brief Engine API.
	 * Used to interface with Engine related data.
	*/
	class Engine {

	public:

		/**
		 * @brief Timer used by engine.
		*/
		class Timer
		{
		public:

			/**
			 * @brief Base constructor.
			*/
			Timer();

			/**
			 * @brief Reset timer.
			*/
			void reset();

			/**
			 * @brief Mark a frame. Usually called after frame generation.
			*/
			void markFrame();

			/**
			 * @brief Get Time elapsed since start.
			 * @return Time since start.
			*/
			Timestamp getTime() const noexcept;

			/**
			 * @brief Get Delta Time.
			 * Delta Time is the time elapsed since last marked frame.
			 * @return Delta Time.
			*/
			Timestamp getDeltaTime() const noexcept { return _deltaTime; }
			std::size_t getFrameCount() const noexcept { return _frameCount; }

		private:

			Timestamp _deltaTime;
			std::size_t _frameCount;
			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _last;
		};

		// Pure Static Class

		Engine() = delete;
		Engine(const Engine&) = delete;
		Engine& operator =(const Engine&) = delete;

		/**
		 * @brief Init Engine.
		 * Used to start and setup Engine.
		*/
		static void init();

		/**
		 * @brief Shutdown Engine.
		 * Used to terminate the engine and wipe leftover data.
		*/
		static void shutdown();

		/**
		 * @brief Get Engine internal timer.
		 * @return Engine internal timer.
		*/
		static const Timer& getTimer() { return _timer; }

	private:

		static Timer _timer;

		friend class WindowsWindow;
		friend class GlfwPlatformsWindow;
	};

}
