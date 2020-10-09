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

void OpenGLRendererAPI::init()
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

void OpenGLRendererAPI::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::clearDepthBuffer() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::setClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::setViewport(Vector2 location, Vector2 size)
{
	glViewport(
		static_cast<GLint>(location.x), 
		static_cast<GLint>(location.y),
		static_cast<GLsizei>(size.x), 
		static_cast<GLsizei>(size.y)
	);
}

void OpenGLRendererAPI::setViewport(UInt x, UInt y, UInt width, UInt height)
{
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::drawIndexed(const Reference<VertexArray>& vertexArray, UInt indexCount)
{
	GLsizei count = indexCount ? static_cast<GLsizei>(indexCount) : static_cast<GLsizei>(vertexArray->getIndexBuffer()->getCount());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
