#include "OpenGLVertexBuffer.h"

#include <Honey/Core/Profiling.h>

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

uint32_t OpenGLVertexBuffer::s_Bound = 0;

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	HNY_PROFILE_FUNCTION();

	glCreateBuffers(1, &_rendererID);
	PerformBinding();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	HNY_PROFILE_FUNCTION();

	glCreateBuffers(1, &_rendererID);
	PerformBinding();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	HNY_PROFILE_FUNCTION();

	unbind();
	glDeleteBuffers(1, &_rendererID);
}

void OpenGLVertexBuffer::bind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound == _rendererID) return;

	PerformBinding();
}

void OpenGLVertexBuffer::unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	PerformUnbinding();
}

bool OpenGLVertexBuffer::isBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	PerformBinding();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::PerformBinding() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	s_Bound = _rendererID;
}

void OpenGLVertexBuffer::PerformUnbinding() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	s_Bound = 0;
}
