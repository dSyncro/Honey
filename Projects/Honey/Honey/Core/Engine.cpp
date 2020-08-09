#include "Engine.h"

#include <Honey/Core/Assertion.h>
#include <Honey/Core/Platform.h>

using namespace std::chrono;
using namespace Honey;

Engine::Timer Engine::_timer = Timer();

void Engine::Init()
{
	bool platformInit = Platform::Init();
	HNY_CORE_ASSERT(platformInit, "Platform initialization failed!");

	Log::Init();
}

void Engine::Shutdown()
{
	Platform::Shutdown();
}


Engine::Timer::Timer()
{
	Reset();
}

void Engine::Timer::Reset()
{
	_start = _last = system_clock::now();
}

void Engine::Timer::MarkFrame()
{
	_frameCount++;
	system_clock::time_point now = system_clock::now();
	_deltaTime = duration_cast<duration<float>>(now - _last).count();
	_last = now;
}

Timestamp Engine::Timer::GetTime() const noexcept
{
	system_clock::time_point now = system_clock::now();
	return duration_cast<duration<float>>(now - _start).count();
}
