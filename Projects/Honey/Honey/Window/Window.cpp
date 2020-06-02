#include "Window.h"

#include <Honey/Platform/GLFW/GlfwPlatformsWindow.h>

using namespace Honey;

Unique<Window> Window::Create(const WindowProperties& properties)
{

#ifdef HNY_PLATFORM_GLFW
	return CreateUnique<GlfwPlatformsWindow>(properties);
#else
	HZ_CORE_ASSERT(false, "Unknown platform!");
	return nullptr;
#endif

}