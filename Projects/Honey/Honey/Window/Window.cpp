#include "Window.h"

#ifdef HNY_PLATFORM_GLFW
#include <Honey/Platform/GLFW/GlfwPlatformsWindow.h>
#elif defined(HNY_PLATFORM_WINDOWS)
#include <Honey/Platform/Windows/WindowsWindow.h>
#endif

using namespace Honey;

Unique<Window> Window::Create(const WindowProperties& properties)
{
#ifdef HNY_PLATFORM_GLFW
	return CreateUnique<GlfwPlatformsWindow>(properties);
#elif defined(HNY_PLATFORM_WINDOWS)
	return CreateUnique<WindowsWindow>(properties);
#else
	HZ_CORE_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif

}
