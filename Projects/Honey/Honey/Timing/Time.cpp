#include "Time.h"

#include "EngineTime.h"

using namespace Honey;

Timestamp Time::GetTime()
{
	return EngineTime::GetTime();
}

Timestamp Time::GetDeltaTime()
{
	return EngineTime::GetDeltaTime();
}

float Time::GetFrameRate()
{
	return 1 / EngineTime::GetDeltaTime();
}

std::size_t Time::GetFrameCount()
{
	return EngineTime::GetFrameCount();
}