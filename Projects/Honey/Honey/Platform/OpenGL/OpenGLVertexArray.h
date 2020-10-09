#pragma once

#include <Honey/Renderer/VertexArray.h>

namespace Honey {

	/**
	 * @brief OpenGL vertex array implementation.
	*/
	class OpenGLVertexArray final : public VertexArray {

	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		/**
		 * @brief Binde vertex array.
		*/
		virtual void bind() const override;

		/**
		 * @brief Unbind vertex array.
		*/
		virtual void unbind() const override;

		/**
		 * @brief Check if vertex array is bound.
		*/
		virtual bool isBound() const override;

		/**
		 * @brief Add vertex buffer to vertex array.
		 * @param buffer The vertex buffer.
		*/
		virtual void addVertexBuffer(const Reference<VertexBuffer>& buffer) override;

		/**
		 * @brief Set index buffer for vertex array.
		 * @param buffer The index buffer.
		*/
		virtual void setIndexBuffer(const Reference<IndexBuffer>& buffer) override;

		/**
		 * @brief Get vertex buffers.
		 * @return The vertex buffers.
		*/
		virtual const std::vector<Reference<VertexBuffer>>& getVertexBuffers() const override { return _vertexBuffers; }

		/**
		 * @brief Get index buffers.
		 * @return The index buffers.
		*/
		virtual const Reference<IndexBuffer>& getIndexBuffer() const override { return _indexBuffer; }

	private:

		std::vector<Reference<VertexBuffer>> _vertexBuffers;
		Reference<IndexBuffer> _indexBuffer;

		UInt _rendererID, _vertexBufferIndex = 0;
		
		static UInt s_Bound;
	};

}
