#pragma once

#include <Honey/Renderer/Buffers/IndexBuffer.h>

namespace Honey {

	class OpenGLIndexBuffer : public IndexBuffer {

	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetCount() const override { return _count; }

	private:

		uint32_t _rendererID;
		uint32_t _count;
	};

}