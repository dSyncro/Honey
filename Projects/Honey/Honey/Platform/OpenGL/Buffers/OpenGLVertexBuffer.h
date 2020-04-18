#pragma once

#include <Honey/Renderer/Buffers/VertexBuffer.h>

namespace Honey {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:

		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:

		uint32_t _rendererID;
	};

}