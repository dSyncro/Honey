#pragma once

#include "Instrumentor.h"

namespace Honey {

	class InstrumentationTimer
	{

	public:

		InstrumentationTimer(const char* name) : _name(name), _isStopped(false)
		{
			_startTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!_isStopped)
				Stop();
		}

		void Stop()
		{
			std::chrono::time_point endTimepoint = std::chrono::steady_clock::now();
			std::chrono::duration<double, std::micro> highResStart = _startTimepoint.time_since_epoch();
			std::chrono::microseconds elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - _startTimepoint);

			Instrumentor::Get().WriteProfile({ _name, highResStart, elapsedTime, std::this_thread::get_id() });

			_isStopped = true;
		}

	private:

		const char* _name;
		std::chrono::time_point<std::chrono::steady_clock> _startTimepoint;
		bool _isStopped;
	};

}