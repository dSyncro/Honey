#pragma once

#include <Honey/Math/Vector/Vector4.h>

namespace Honey {

	struct SpriteRendererComponent {

		SpriteRendererComponent() : Color(Math::Vector4::One) {}
		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Math::Vector4& color) 
			: Color(color) {}

		Math::Vector4 Color;
	};

}
