#include "OpenGLContext.h"

#include <Honey/Core.h>
#include <Honey/Logging/Log.h>

#include <glad/glad.h>

using namespace Honey;

OpenGLContext::OpenGLContext(GLFWwindow* handle) : _handle(handle) {}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(_handle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HNY_CORE_ASSERT(status, "Failed to init GLAD!");
	
	HNY_CORE_INFO("OpenGL Info");
	HNY_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
	HNY_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
	HNY_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(_handle);
}