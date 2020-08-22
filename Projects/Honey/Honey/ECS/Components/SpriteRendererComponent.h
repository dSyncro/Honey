#pragma once

#include <Honey/Renderer/2D/Sprite.h>

namespace Honey {

	struct SpriteRendererComponent {
		
		SpriteRendererComponent() : Tint(Math::Vector4::One) {};
		SpriteRendererComponent(const Reference<Sprite>& sprite, Math::Vector4 tint = Math::Vector4::One)
			: Sprite(sprite), Tint(tint) { }

		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;

		Reference<Sprite> Sprite;
		Math::Vector4 Tint;
	};

}
