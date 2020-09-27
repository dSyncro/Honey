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
		TextComponent(const TextComponent&) = default;
		TextComponent(const std::string& text) : text(text) {}

		std::string text; /** @brief Text to display. */
		Reference<FontAtlas> atlas; /** @brief Font atlas used to display text. */
	};

}
