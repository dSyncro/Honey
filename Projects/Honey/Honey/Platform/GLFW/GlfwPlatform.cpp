#include <Honey/Core.h>
#include <Honey/Core/Platform.h>

#include <GLFW/glfw3.h>

using namespace Honey;

static void GLFWErrorCallback(int error, const char* description)
{
	HNY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

bool Platform::Init()
{
	int success = glfwInit();
	HNY_CORE_ASSERT(success, "Could not init GLFW!");
	glfwSetErrorCallback(GLFWErrorCallback);
	return true;
}

void Platform::Shutdown()
{
	glfwTerminate();
}

Platform::API Platform::GetAPI() { return API::GLFW; }
