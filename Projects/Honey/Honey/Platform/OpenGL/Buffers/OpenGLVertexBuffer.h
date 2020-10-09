#pragma once

#include <Honey/Renderer/Buffers/VertexBuffer.h>

namespace Honey {

	/**
	 * @brief OpenGL vertex buffer implementation.
	*/
	class OpenGLVertexBuffer final : public VertexBuffer {

	public:

		/**
		 * @brief Construct OpenGLVertexBuffer.
		 * @param size Size in bytes.
		*/
		OpenGLVertexBuffer(UInt size);

		/**
		 * @brief Construct OpenGLVertexBuffer.
		 * @param vertices The vertices.
		 * @param size Size in bytes.
		*/
		OpenGLVertexBuffer(Float* vertices, UInt size);

		virtual ~OpenGLVertexBuffer();
		
		/**
		 * @brief Bind vertex buffer.
		*/
		virtual void bind() const override;

		/**
		 * @brief Unbind vertex buffer.
		*/
		virtual void unbind() const override;

		/**
		 * @brief Check if vertex buffer is bound.
		*/
		virtual bool isBound() const override;

		/**
		 * @brief Set vertex buffer data.
		 * @param data New data.
		 * @param size Data size in bytes.
		*/
		virtual void setData(const void* data, UInt size) override;

		/**
		 * @brief Set vertex buffer layout.
		 * @param layout The layout.
		*/
		virtual void setLayout(const BufferLayout& layout) override { _layout = layout; }

		/**
		 * @brief Get vertex buffer layout.
		 * @return The vertex buffer layout.
		*/
		virtual const BufferLayout& getLayout() const override { return _layout; }

	private:

		UInt _rendererID;
		BufferLayout _layout;

		void performBinding() const;
		void performUnbinding() const;

		static UInt s_Bound;
	};

}
