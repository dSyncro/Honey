#pragma once

#include <Honey/Renderer/VertexArray.h>

namespace Honey {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> & buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> & buffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return _vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return _indexBuffer; }

	private:

		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;

		uint32_t _rendererID;
	};

}