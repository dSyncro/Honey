#pragma once

#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	/**
	 * @brief Glyph representation.
	*/
	struct Glyph {

		Glyph() = default;

		/**
		 * @brief Character associated to glyph.
		*/
		char character = 0;

		/**
		 * @brief Glyph texture coordinates in parent atlas.
		*/
		Quad::TextureCoordinates uv = Quad::DefaultTextureCoords;

		/**
		 * @brief Glyph bounding box.
		*/
		Math::Rect boundingBox = Math::Rect();

		/**
		 * @brief Glyph bearing/offset.
		*/
		Math::Vector2 offset = Math::Vector2::zero();

		/**
		 * @brief Glyph advance.
		 * That is the horizantal distance to advance in order to
		 * properly print a new glyph after this.
		*/
		Float advance = 0.0f;

	};

}
