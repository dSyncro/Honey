#include <Honey/Core/Log.h>
#include <Honey/Core/Platform.h>

using namespace Honey;

bool Platform::Init()
{
	return true;
}

void Platform::Shutdown()
{
	// TODO: Perform cleanup
}

Platform::API Platform::GetAPI() { return API::GLFW; }
