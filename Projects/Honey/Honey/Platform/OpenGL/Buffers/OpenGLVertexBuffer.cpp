#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

using namespace Honey;

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

	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

void OpenGLVertexBuffer::Unbind() const
{
	HNY_PROFILE_FUNCTION();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}