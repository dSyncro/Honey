#include "Time.h"

#include "EngineTime.h"

using namespace Honey;

Timestamp Time::GetTime()
{
	return EngineTime::Time;
}

Timestamp Time::GetDeltaTime()
{
	return EngineTime::DeltaTime;
}

float Time::GetFrameRate()
{
	return 1 / EngineTime::DeltaTime;
}

unsigned int Time::GetFrameCount()
{
	return EngineTime::FrameCount;
}