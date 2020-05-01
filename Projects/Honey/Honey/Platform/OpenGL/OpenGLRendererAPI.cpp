#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

#include <Honey/Logging/Log.h>

using namespace Honey;

void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
{
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         HNY_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       HNY_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          HNY_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: HNY_CORE_TRACE(message); return;
	}

	HNY_CORE_ASSERT(false, "Unknown severity level!");
}

void OpenGLRendererAPI::Init()
{

#ifdef HNY_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
}

void OpenGLRendererAPI::DrawIndexed(const Reference<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
