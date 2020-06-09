#pragma once

#include <Honey/Renderer/Buffers/FrameBuffer.h>

namespace Honey {

	class OpenGLFrameBuffer : public FrameBuffer {

	public:

		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetColorAttachmentRendererID() const override { return _colorAttachment; }

		virtual const FrameBufferSpecification& GetSpecification() const override { return _specification; }

	private:

		FrameBufferSpecification _specification;
		uint32_t _rendererID;
		uint32_t _colorAttachment, _depthAttachment;

	};

}