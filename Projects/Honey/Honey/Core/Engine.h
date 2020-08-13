#pragma once

#include <chrono>

#include <Honey/Timing/Timestamp.h>

namespace Honey {

	class Engine {

	public:

		class Timer
		{
		public:

			Timer();

			void Reset();
			void MarkFrame();

			Timestamp GetTime() const noexcept;
			Timestamp GetDeltaTime() const noexcept { return _deltaTime; }
			std::size_t GetFrameCount() const noexcept { return _frameCount; }

		private:

			Timestamp _deltaTime;
			std::size_t _frameCount;
			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _last;
		};

		Engine() = delete;
		Engine(const Engine&) = delete;
		Engine& operator =(const Engine&) = delete;

		static void Init();
		static void Shutdown();

		static const Timer& GetTimer() { return _timer; }

	private:

		static Timer _timer;

		friend class WindowsWindow;
		friend class GlfwPlatformsWindow;
	};

}
