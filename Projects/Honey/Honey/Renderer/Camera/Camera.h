#pragma once

#include <glm/glm.hpp>

namespace Honey {

	struct Camera {

		Camera() = default;
		Camera(const glm::mat4& projectionMatrix) : _projection(projectionMatrix) {}
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return _projection; }

	protected:

		glm::mat4 _projection = glm::mat4(1.0f);
	};

}
