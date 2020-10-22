/**
 * @file TextComponent.h
*/

#pragma once

#include <string>
#include <Honey/Renderer/2D/UI/Text/FontAtlas.h>

namespace Honey {

	/**
	 * @brief Used to render text.
	*/
	struct TextComponent {

		TextComponent() = default;
		~TextComponent() = default;

		/**
		 * @brief Construct TextComponent.
		 * @param text The text.
		 * @param color Text color.
		*/
		TextComponent(const std::string& text, const Color& color = Color::black()) : text(text), color(color) {}

		TextComponent(const TextComponent&) = default;

		std::string text; /** @brief Text to display. */
		Color color; /** @brief Text color. */
		Reference<FontAtlas> atlas; /** @brief Font atlas used to display text. */
	};

}
