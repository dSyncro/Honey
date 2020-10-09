#include <Honey/Core.h>
#include <Honey/Core/Platform.h>

#include <GLFW/glfw3.h>

using namespace Honey;

/**
 * @brief GLFW error callback.
 * @param error Error code.
 * @param description Error description.
*/
static void GLFWErrorCallback(int error, const char* description)
{
	HNY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

bool Platform::init()
{
	// Init glfw
	int success = glfwInit();
	HNY_CORE_ASSERT(success, "Could not init GLFW!");

	// Set error callback
	glfwSetErrorCallback(GLFWErrorCallback);
	return true;
}

void Platform::shutdown()
{
	// Terminate glfw
	glfwTerminate();
}

Platform::API Platform::getAPI() { return API::GLFW; }
