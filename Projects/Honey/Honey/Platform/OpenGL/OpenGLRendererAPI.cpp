#include "OpenGLRendererAPI.h"

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;
using namespace Honey::Math;

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
		case GL_DEBUG_SEVERITY_HIGH:         HNY_CORE_CRITICAL (message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       HNY_CORE_ERROR    (message); return;
		case GL_DEBUG_SEVERITY_LOW:          HNY_CORE_WARN     (message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: HNY_CORE_TRACE    (message); return;
	}

	HNY_CORE_ASSERT(false, "Unknown severity level!");
}

void OpenGLRendererAPI::Init()
{
	HNY_PROFILE_FUNCTION();

#ifdef HNY_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::ClearDepthBuffer() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::SetViewport(Vector2 location, Vector2 size)
{
	glViewport((uint32_t)location.x, (uint32_t)location.y, (uint32_t)size.x, (uint32_t)size.y);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount)
{
	uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
