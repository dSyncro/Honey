#pragma once

#include <string>
#include <Honey/Renderer/2D/UI/Text/FontAtlas.h>

namespace Honey {

	struct TextComponent {

		TextComponent() = default;
		~TextComponent() = default;
		TextComponent(const TextComponent&) = default;
		TextComponent(const std::string& text) : Text(text) {}

		std::string Text;
		Reference<FontAtlas> Atlas;
	};

}
