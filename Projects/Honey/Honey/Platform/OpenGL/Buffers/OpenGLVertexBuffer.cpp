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

	glGenBuffers(1, &_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	HNY_PROFILE_FUNCTION();

	glGenBuffers(1, &_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	HNY_PROFILE_FUNCTION();

	glDeleteBuffers(1, &_rendererID);
}

void OpenGLVertexBuffer::Bind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound == _rendererID) return;

	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	s_Bound = _rendererID;
}

void OpenGLVertexBuffer::Unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	s_Bound = 0;
}

bool OpenGLVertexBuffer::IsBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
