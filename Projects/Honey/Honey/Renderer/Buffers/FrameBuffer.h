#pragma once

#include <Honey/Core/MemoryManagement.h>

namespace Honey {

	struct FrameBufferSpecification {

		uint32_t Width, Height;

	};

	class FrameBuffer {

	public:

		virtual ~FrameBuffer() = default;

		/**
		 * @brief Get specification of this frame buffer.
		 * @return This frame buffer specification.
		 */
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		/**
		 * @brief Create Frame Buffer.
		 * @param specification -> Frame Buffer specification.
		 * @return The frame buffer.
		 */
		static Reference<FrameBuffer> Create(const FrameBufferSpecification& specification);
	};

}