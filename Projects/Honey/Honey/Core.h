#pragma once

#include "Core/Assertion.h"
#include "Core/Profiling.h"
#include "Core/MemoryTracking.h"
// #include "Core/DLLAutomation.h"

// Bitmasking
#define BIT(x) 1 << x

// Event Callback Binding
#define HNY_BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)