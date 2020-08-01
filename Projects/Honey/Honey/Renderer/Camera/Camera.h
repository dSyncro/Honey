#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Honey {

	struct Camera {

		Camera(const glm::mat4& projectionMatrix) : _projection(projectionMatrix) {}
		const glm::mat4& GetProjection() const { return _projection; }

		void SetOrthographic(float left, float right, float bottom, float top) { _projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); }

	private:

		glm::mat4 _projection;
	};

}
