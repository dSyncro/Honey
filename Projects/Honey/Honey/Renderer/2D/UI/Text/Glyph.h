#pragma once

#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	struct Glyph {

		Glyph() = default;

		char Character = 0;
		Quad::TextureCoordinates UV = Quad::DefaultTextureCoords;
		Math::Rect BoundingBox = Math::Rect();
		Math::Vector2 Bearing = Math::Vector2::Zero;
		Math::Vector2 ClassicBearing = Math::Vector2::Zero;
		float ClassicAdv = 0.0f;
		float Advance = 0.0f;

	};

}
