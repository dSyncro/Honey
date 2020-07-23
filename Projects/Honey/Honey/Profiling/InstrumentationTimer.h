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
			if (!_isStopped) Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ _startTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(_startTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ _name, highResStart, elapsedTime, std::this_thread::get_id() });

			_isStopped = true;
		}

	private:

		const char* _name;
		std::chrono::time_point<std::chrono::steady_clock> _startTimepoint;
		bool _isStopped;
	};
}