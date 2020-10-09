#include <Honey/Core.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>

extern "C" {
#include <GLFW/glfw3.h>
#include <glad/glad.h>
}

using namespace Honey;

OpenGLContext::OpenGLContext(void* handle) : _handle(handle)
{
	HNY_CORE_ASSERT(_handle, "Window handle is null!");
}

void OpenGLContext::init()
{
	HNY_PROFILE_FUNCTION();

	glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(_handle));
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HNY_CORE_ASSERT(status, "Failed to init GLAD!");

	HNY_CORE_INFO("## OpenGL Info ##");
	HNY_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
	HNY_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	HNY_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
	HNY_CORE_INFO("#################");
}

void OpenGLContext::swapBuffers()
{
	HNY_PROFILE_FUNCTION();

	glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(_handle));
}
