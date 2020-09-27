#pragma once

#include <Honey/Renderer/Buffers/VertexBuffer.h>

namespace Honey {

	class OpenGLVertexBuffer final : public VertexBuffer {

	public:

		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual bool isBound() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void SetLayout(const BufferLayout& layout) override { _layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return _layout; }

	private:

		uint32_t _rendererID;
		BufferLayout _layout;

		void PerformBinding() const;
		void PerformUnbinding() const;

		static uint32_t s_Bound;
	};

}
