#pragma once

#include <Honey/Renderer/Buffers/FrameBuffer.h>

namespace Honey {

	/**
	 * @brief OpenGL Frame Buffer implementation.
	*/
	class OpenGLFrameBuffer : public FrameBuffer {

	public:

		/**
		 * @brief Construct OpenGLFrameBuffer from specifications.
		 * @param specification The specifications.
		*/
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		/**
		 * @brief Invalidate frame buffer.
		*/
		void invalidate();

		/**
		 * @brief Free frame buffer resources.
		*/
		void free();

		/**
		 * @brief Bind frame buffer.
		*/
		virtual void bind() const override;

		/**
		 * @brief Unbind frame buffer.
		*/
		virtual void unbind() const override;

		/**
		 * @brief Check if frame buffer is already bound.
		*/
		virtual bool isBound() const override;

		/**
		 * @see FrameBuffer::getColorAttachmentRendererID()
		*/
		virtual UInt getColorAttachmentRendererID() const override { return _colorAttachment; }

		/**
		 * @see FrameBuffer::getSpecification()
		*/
		virtual const FrameBufferSpecification& getSpecification() const override { return _specification; }

		/**
		 * @see FrameBuffer::resize()
		*/
		virtual void resize(UInt width, UInt height) override;

	private:

		FrameBufferSpecification _specification;
		UInt _rendererID = 0;
		UInt _colorAttachment = 0, _depthAttachment = 0;

		static UInt s_Bound;
	};

}
