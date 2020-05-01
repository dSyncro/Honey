#include "Window.h"

#include <Honey/Platform/Window/WinWindow.h>

using namespace Honey;

Unique<Window> Window::Create(const WindowProperties& properties)
{

#ifdef HNY_PLATFORM_WINDOWS
	return CreateUnique<WinWindow>(properties);
#else
	HZ_CORE_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif

}