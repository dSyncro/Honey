#pragma once

#include <Honey/Core/Color.h>
#include <Honey/Renderer/2D/Sprite.h>

namespace Honey {

	struct SpriteRendererComponent {
		
		SpriteRendererComponent() : Tint(Color::White) {};
		SpriteRendererComponent(const Reference<Sprite>& sprite, const Color& tint = Color::White)
			: Sprite(sprite), Tint(tint) { }

		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;

		Reference<Sprite> Sprite;
		Color Tint;
	};

}
