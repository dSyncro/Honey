#include "Engine.h"

#include <Honey/Core/Assertion.h>
#include <Honey/Core/Platform.h>

using namespace std::chrono;
using namespace Honey;

Engine::Timer Engine::_timer = Timer();

void Engine::init()
{
	// Initialize platform first
	bool platformInit = Platform::init();
	HNY_CORE_ASSERT(platformInit, "Platform initialization failed!");

	// Initialize Logging
	Log::init();
}

void Engine::shutdown()
{
	// Clear Platform information
	Platform::shutdown();
}


Engine::Timer::Timer()
{
	// Set timer data to default
	reset();
}

void Engine::Timer::reset()
{
	// Set timer data to now
	_start = _last = system_clock::now();
}

void Engine::Timer::markFrame()
{
	_frameCount++; // increment frame count

	// Calculate delta time
	system_clock::time_point now = system_clock::now();
	_deltaTime = duration_cast<duration<float>>(now - _last).count();

	_last = now; // Mark
}

Timestamp Engine::Timer::getTime() const noexcept
{
	system_clock::time_point now = system_clock::now();
	return duration_cast<duration<Float>>(now - _start).count();
}
