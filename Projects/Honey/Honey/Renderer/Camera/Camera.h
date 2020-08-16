#pragma once

#include <Honey/Math/Matrix/Matrix4x4.h>

namespace Honey {

	struct Camera {

		Camera() = default;
		Camera(const Math::Matrix4x4& projectionMatrix) : _projection(projectionMatrix) {}
		virtual ~Camera() = default;

		const Math::Matrix4x4& GetProjection() const { return _projection; }

	protected:

		Math::Matrix4x4 _projection = Math::Matrix4x4::Identity;
	};

}
