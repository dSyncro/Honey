#pragma once

#include <Honey/Renderer/Buffers/IndexBuffer.h>

namespace Honey {

	class OpenGLIndexBuffer final : public IndexBuffer {

	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual bool isBound() const override;

		inline virtual uint32_t GetCount() const override { return _count; }

	private:

		uint32_t _rendererID;
		uint32_t _count;

		static uint32_t s_Bound;
	};

}
