#include "Window.h"

#include <Honey/Platform/GLFW/GlfwPlatformsWindow.h>
#include <Honey/Platform/Windows/WindowsWindow.h>

using namespace Honey;

Unique<Window> Window::Create(const WindowProperties& properties)
{

#ifdef HNY_PLATFORM_WINDOWS
	return CreateUnique<WindowsWindow>(properties);
#elif defined(HNY_PLATFORM_GLFW)
	return CreateUnique<GlfwPlatformsWindow>(properties);
#else
	HZ_CORE_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif

}
