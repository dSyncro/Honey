#pragma once

#include <Honey/Renderer/Buffers/FrameBuffer.h>

namespace Honey {

	class OpenGLFrameBuffer : public FrameBuffer {

	public:

		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();
		void Free();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual bool isBound() const override;
		virtual uint32_t GetColorAttachmentRendererID() const override { return _colorAttachment; }

		virtual const FrameBufferSpecification& GetSpecification() const override { return _specification; }

		virtual void Resize(uint32_t width, uint32_t height) override;

	private:

		FrameBufferSpecification _specification;
		uint32_t _rendererID = 0;
		uint32_t _colorAttachment = 0, _depthAttachment = 0;

		static uint32_t s_Bound;
	};

}
