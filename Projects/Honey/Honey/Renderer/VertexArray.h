#pragma once

#include <Honey/Renderer/Buffers.h>

namespace Honey {

	class VertexArray {

	public:

		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& buffer) = 0;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}