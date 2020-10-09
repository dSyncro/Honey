#pragma once

#include <Honey/Core.h>
#include <Honey/Core/IBindable.h>
#include <Honey/Renderer/Buffers/BufferLayout.h>

namespace Honey {

	/**
	 * @brief Vertex buffer implementation.
	*/
	class VertexBuffer : public IBindable {

	public:

		virtual ~VertexBuffer() = default;

		/**
		 * @brief Set buffer layout.
		 * @param layout New buffer layout.
		*/
		virtual void setLayout(const BufferLayout& layout) = 0;

		/**
		 * @brief Get buffer layout.
		 * @return Buffer layout of this vertex buffer.
		*/
		virtual const BufferLayout& getLayout() const = 0;

		/**
		 * @brief Set vertex buffer data.
		 * @param data New data.
		 * @param size Size of data in bytes.
		*/
		virtual void setData(const void* data, UInt size) = 0;

		/**
		 * @brief Create new vertex buffer of specified size.
		 * @param size The size in bytes.
		 * @return A new memory managed vertex buffer.
		*/
		static Reference<VertexBuffer> create(UInt size);

		/**
		 * @brief Create new vertex buffer from vertices.
		 * @param vertices The vertices.
		 * @param size The size in bytes.
		 * @return A new memory managed vertex buffer.
		*/
		static Reference<VertexBuffer> create(Float* vertices, UInt size);
	};

}
