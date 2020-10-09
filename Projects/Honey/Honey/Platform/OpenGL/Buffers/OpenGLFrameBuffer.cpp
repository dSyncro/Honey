#include "OpenGLFrameBuffer.h"

#include <Honey/Core/Assertion.h>

#include <glad/glad.h>

using namespace Honey;

UInt OpenGLFrameBuffer::s_Bound = 0;

OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& specification) : _specification(specification)
{
	// Invalidate new framebuffer
	invalidate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	// Free resources
	free();
}

void OpenGLFrameBuffer::invalidate()
{
	// If already exist free old one
	if (_rendererID) free();

	// If size is not valid return
	if (_specification.Width <= 0 || _specification.Height <= 0) return;

	// Create and bind framebuffer
	glCreateFramebuffers(1, &_rendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

	// Create and bind color attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
	glBindTexture(GL_TEXTURE_2D, _colorAttachment);

	// Set its values
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specification.Width, _specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach color attachment to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

	// Create and bind depth attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
	glBindTexture(GL_TEXTURE_2D, _depthAttachment);

	// Set its values and attach to frame buffer
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _specification.Width, _specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

	// At this point frame buffer must be complete
	HNY_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame Buffer is incomplete!");

	// We can unbind frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::free()
{
	glDeleteFramebuffers(1, &_rendererID); // Delete buffer
	glDeleteTextures(1, &_colorAttachment); // Delete color attachment
	glDeleteTextures(1, &_depthAttachment); // Delete depth attachment
}

void OpenGLFrameBuffer::bind() const
{
	// If already bound return
	if (s_Bound == _rendererID) return;

	// Bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, s_Bound = _rendererID);

	// Set viewport
	glViewport(0, 0, _specification.Width, _specification.Height);
}

void OpenGLFrameBuffer::unbind() const
{
	// If already not bound return
	if (s_Bound != _rendererID) return;

	glBindFramebuffer(GL_FRAMEBUFFER, s_Bound = 0); // Unbind framebuffer
}

bool OpenGLFrameBuffer::isBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLFrameBuffer::resize(UInt width, UInt height)
{
	// Set new dimensions
	_specification.Width = width;
	_specification.Height = height;
	invalidate(); // Invalidate framebuffer
}
