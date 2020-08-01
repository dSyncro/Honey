#pragma once

#include <glm/glm.hpp>

namespace Honey {

	struct TransformComponent {

		TransformComponent() : Transform(glm::mat4(1.0f)) {}
		~TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& trasform)
			: Transform(trasform) { }

		glm::mat4 Transform;

		operator glm::mat4&() { return Transform; }
		operator const glm::mat4&() const { return Transform; }
	};

}