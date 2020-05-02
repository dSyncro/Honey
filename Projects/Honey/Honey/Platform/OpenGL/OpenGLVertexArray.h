#pragma once

#include <Honey/Renderer/VertexArray.h>

namespace Honey {

	class OpenGLVertexArray final : public VertexArray {

	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& buffer) override;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const override { return _vertexBuffers; }
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const override { return _indexBuffer; }

	private:

		std::vector<Reference<VertexBuffer>> _vertexBuffers;
		Reference<IndexBuffer> _indexBuffer;

		uint32_t _rendererID;
	};

}