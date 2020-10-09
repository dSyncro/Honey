#pragma once

#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	/**
	 * @brief Camera extension.
	*/
	class SceneCamera : public Camera {

	public:

		SceneCamera() = default;
		virtual ~SceneCamera() = default;

		/**
		 * @brief Set orthographic projection.
		 * @param size Orthographic size.
		 * @param nearClip Near clip distance.
		 * @param farClip Far clip distance.
		*/
		void setOrthographic(Float size, Float nearClip, Float farClip);

		/**
		 * @brief Set viewport size.
		 * @param width Viewport width.
		 * @param height Viewport height.
		*/
		void setViewportSize(UInt width, UInt height);

	private:

		void recalculateProjection();

		Float _orthoSize = 10.0f;
		Float _aspectRatio = 1.0f;
		Float _orthoNear = -1.0f; Float _orthoFar = 1.0f;
	};

}
