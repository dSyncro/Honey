#pragma once

#include <glm/glm.hpp>

#include "MathFunctions.h"
#include "Random.h"

namespace Honey {

	namespace Math {

		struct Vector4 {

			constexpr static glm::vec4 Zero = glm::vec4(0.0f);
			constexpr static glm::vec4 One = glm::vec4(1.0f);

			Vector4(float value = 0.0f) : X(value), Y(value), Z(value), W(value) {}
			Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

			operator glm::vec4() const { return glm::vec4(X, Y, Z, W); }

			float X, Y, Z, W;

		};

		struct Matrix4 {

			constexpr static glm::mat4 Identity = glm::mat4(1.0f);

		};

	}
}