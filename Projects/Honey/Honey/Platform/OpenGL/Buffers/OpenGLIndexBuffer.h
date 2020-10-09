#pragma once

#include <Honey/Renderer/Buffers/IndexBuffer.h>

namespace Honey {

	/**
	 * @brief OpenGL index buffer implementation.
	*/
	class OpenGLIndexBuffer final : public IndexBuffer {

	public:

		/**
		 * @brief Construct OpenGLIndexBuffer.
		 * @param indices Pointer to the indices.
		 * @param count Index count.
		*/
		OpenGLIndexBuffer(UInt* indices, UInt count);
		virtual ~OpenGLIndexBuffer();

		/**
		 * @brief Bind index buffer.
		*/
		virtual void bind() const override;

		/**
		 * @brief Unbind index buffer.
		*/
		virtual void unbind() const override;

		/**
		 * @brief Check if index buffer is bound.
		*/
		virtual bool isBound() const override;

		/**
		 * @brief Get index count.
		 * @return Index count.
		*/
		virtual UInt getCount() const override { return _count; }

	private:

		UInt _rendererID;
		UInt _count;

		static UInt s_Bound;
	};

}
