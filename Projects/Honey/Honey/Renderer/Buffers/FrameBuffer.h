#pragma once

#include <Honey/Core.h>
#include <Honey/Core/IBindable.h>

namespace Honey {

	/**
	 * @brief Frame buffer specification.
	 * It holds data that specifies the frame buffer working mode.
	*/
	struct FrameBufferSpecification {

		UInt Width, Height;

	};

	/**
	 * @brief Abstract Frame Buffer.
	*/
	class FrameBuffer : public IBindable {

	public:

		virtual ~FrameBuffer() = default;

		/**
		 * @brief Get specification of this frame buffer.
		 * @return This frame buffer specification.
		 */
		virtual const FrameBufferSpecification& getSpecification() const = 0;

		/**
		 * @brief Get color attachment ID.
		 * @return Color attachment renderer ID.
		*/
		virtual UInt getColorAttachmentRendererID() const = 0;

		/**
		 * @brief Resize frame buffer.
		 * @param width New width.
		 * @param height New height.
		*/
		virtual void resize(UInt width, UInt height) = 0;

		/**
		 * @brief Create Frame Buffer.
		 * @param specification -> Frame Buffer specification.
		 * @return The frame buffer.
		 */
		static Reference<FrameBuffer> create(const FrameBufferSpecification& specification);
	};

}
