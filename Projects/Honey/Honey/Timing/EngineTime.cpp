#include "EngineTime.h"

using namespace Honey;

Timestamp EngineTime::Time = 0.0f;
Timestamp EngineTime::DeltaTime = 0.0f;
std::size_t EngineTime::FrameCount = 0;