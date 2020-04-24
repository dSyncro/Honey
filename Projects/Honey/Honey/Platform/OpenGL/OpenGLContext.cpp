#include "OpenGLContext.h"

#include <Honey/Core.h>
#include <Honey/Logging/Log.h>

#include <glad/glad.h>

using namespace Honey;

OpenGLContext::OpenGLContext(GLFWwindow* handle) : _handle(handle) {}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


void OpenGLContext::Init()
{
	glfwMakeContextCurrent(_handle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HNY_CORE_ASSERT(status, "Failed to init GLAD!");
	
	HNY_CORE_INFO("## OpenGL Info ##");
	HNY_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
	HNY_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
	HNY_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
	HNY_CORE_INFO("#################");

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(_handle);
}