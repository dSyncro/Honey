#pragma once

#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	struct Glyph {

		Glyph() = default;

		char Character = 0;
		Math::Rect Face = Math::Rect();
		Quad::TextureCoordinates UV = Quad::DefaultTextureCoords;
		Math::Vector2 Bearing = Math::Vector2::Zero;
		float Advance = 0.0f;

	};

}
