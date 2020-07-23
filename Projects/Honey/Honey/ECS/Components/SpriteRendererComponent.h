#pragma once

#include <glm/glm.hpp>

namespace Honey {

	struct SpriteRendererComponent {

		SpriteRendererComponent() : Color(glm::vec4(1.0f)) {}
		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) 
			: Color(color) {}

		glm::vec4 Color;
	};

}