#pragma once

#include <Honey/Renderer/Buffers.h>

namespace Honey {

	/**
	 * @brief VertexArray abstraction.
	*/
	class VertexArray : public IBindable {

	public:

		virtual ~VertexArray() = default;

		/**
		 * @brief Add vertex buffer to this vertex array.
		 * @param buffer The vertex buffer.
		*/
		virtual void addVertexBuffer(const Reference<VertexBuffer>& buffer) = 0;

		/**
		 * @brief Set index buffer to this vertex array.
		 * @param buffer The index buffer.
		*/
		virtual void setIndexBuffer(const Reference<IndexBuffer>& buffer) = 0;

		/**
		 * @brief Get vertex buffers attached to this vertex array.
		 * @return The vertex buffers.
		*/
		virtual const std::vector<Reference<VertexBuffer>>& getVertexBuffers() const = 0;

		/**
		 * @brief Get index buffer attached to this vertex array.
		 * @return The index buffer.
		*/
		virtual const Reference<IndexBuffer>& getIndexBuffer() const = 0;

		/**
		 * @brief Create VertexArray.
		 * @return A new memory managed VertexArray.
		*/
		static Reference<VertexArray> create();
	};

}
