#include "OpenGLVertexBuffer.h"

#include <Honey/Core/Profiling.h>

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

UInt OpenGLVertexBuffer::s_Bound = 0;

OpenGLVertexBuffer::OpenGLVertexBuffer(UInt size)
{
	HNY_PROFILE_FUNCTION();
	glCreateBuffers(1, &_rendererID);
	performBinding();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(Float* vertices, UInt size)
{
	HNY_PROFILE_FUNCTION();

	glCreateBuffers(1, &_rendererID);
	performBinding();
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

	performBinding();
}

void OpenGLVertexBuffer::unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	performUnbinding();
}

bool OpenGLVertexBuffer::isBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLVertexBuffer::setData(const void* data, UInt size)
{
	performBinding();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::performBinding() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	s_Bound = _rendererID;
}

void OpenGLVertexBuffer::performUnbinding() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	s_Bound = 0;
}
