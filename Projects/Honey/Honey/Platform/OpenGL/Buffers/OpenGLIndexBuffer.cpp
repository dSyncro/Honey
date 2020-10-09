#include "OpenGLIndexBuffer.h"

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

UInt OpenGLIndexBuffer::s_Bound = 0;

OpenGLIndexBuffer::OpenGLIndexBuffer(UInt* indices, UInt count) : _count(count)
{
	// Create buffer
	glCreateBuffers(1, &_rendererID);

	// Setup data
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(UInt), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	// Unbind buffer and then delete it.
	unbind();
	glDeleteBuffers(1, &_rendererID);
}

void OpenGLIndexBuffer::bind() const
{
	// Bind only if not already bound
	if (s_Bound == _rendererID) return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
	s_Bound = _rendererID;
}

void OpenGLIndexBuffer::unbind() const
{
	// Unbind only if bound
	if (s_Bound != _rendererID) return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	s_Bound = 0;
}

bool OpenGLIndexBuffer::isBound() const
{
	return s_Bound == _rendererID;
}
