#include "OpenGLFrameBuffer.h"

#include <Honey/Core/Assertion.h>

#include <glad/glad.h>

using namespace Honey;

OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& specification) : _specification(specification)
{
	Invalidate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &_rendererID);
}

void OpenGLFrameBuffer::Invalidate()
{
	glCreateFramebuffers(1, &_rendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

	glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
	glBindTexture(GL_TEXTURE_2D, _colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specification.Width, _specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
	glBindTexture(GL_TEXTURE_2D, _depthAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _specification.Width, _specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

	HNY_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame Buffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);
}

void OpenGLFrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}