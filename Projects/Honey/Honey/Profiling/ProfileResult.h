#pragma once

#include <chrono>
#include <string>
#include <thread>

namespace Honey {

	struct ProfileResult
	{
		std::string Name;
		std::chrono::duration<double, std::micro> Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

}