#pragma once

#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	struct Glyph {

		Glyph() = default;

		char Character = 0;
		Quad::TextureCoordinates UV = Quad::DefaultTextureCoords;
		Math::Rect BoundingBox = Math::Rect();
		Math::Vector2 Offset = Math::Vector2::Zero;
		float Advance = 0.0f;

	};

}
