#include "OpenGLIndexBuffer.h"

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

uint32_t OpenGLIndexBuffer::s_Bound = 0;

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : _count(count)
{
	glCreateBuffers(1, &_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	unbind();
	glDeleteBuffers(1, &_rendererID);
}

void OpenGLIndexBuffer::bind() const
{
	if (s_Bound == _rendererID) return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
	s_Bound = _rendererID;
}

void OpenGLIndexBuffer::unbind() const
{
	if (s_Bound != _rendererID) return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	s_Bound = 0;
}

bool OpenGLIndexBuffer::isBound() const
{
	return s_Bound == _rendererID;
}
