#pragma once

#include <Honey/Math/Matrix/Matrix4x4.h>

namespace Honey {

	/**
	 * @brief Camera representation.
	*/
	struct Camera {

		Camera() = default;

		/**
		 * @brief Construct Camera from its projection.
		 * @param projectionMatrix The projection.
		*/
		Camera(const Math::Matrix4x4& projectionMatrix) : _projection(projectionMatrix) {}

		virtual ~Camera() = default;

		/**
		 * @brief Get camera projection.
		 * @return Projection of the camera.
		*/
		const Math::Matrix4x4& getProjection() const { return _projection; }

	protected:

		Math::Matrix4x4 _projection = Math::Matrix4x4::identity();
	};

}
