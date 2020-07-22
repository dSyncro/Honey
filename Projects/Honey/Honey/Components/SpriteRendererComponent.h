#pragma once

#include <glm/glm.hpp>

namespace Honey {

	struct SpriteRendererComponent {

		SpriteRendererComponent() = default;
		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) 
			: Color(color) {}

		glm::vec4 Color;
	};

}