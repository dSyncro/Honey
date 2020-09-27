#pragma once

#include <Honey/Core/Color.h>
#include <Honey/Renderer/2D/Sprite.h>

namespace Honey {

	/**
	 * @brief Renderer for sprites.
	*/
	struct SpriteRendererComponent {
		
		SpriteRendererComponent() : tint(Color::white()) {};
		SpriteRendererComponent(const Reference<Sprite>& sprite, const Color& tint = Color::white())
			: sprite(sprite), tint(tint) { }

		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;

		/**
		 * @brief Sprite to render.
		*/
		Reference<Sprite> sprite;

		/**
		 * @brief Sprite tint.
		*/
		Color tint;
	};

}
