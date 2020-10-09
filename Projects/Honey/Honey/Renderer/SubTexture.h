#pragma once

#include "Texture.h"

#include <Honey/Math/Math.h>
#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	/**
	 * @brief 2D Subtexture.
	 * Used for sprites, spritesheets and UV maps.
	*/
	class SubTexture2D {

	public:

		/**
		 * @brief Construct SubTexture2D.
		 * @param texture Source texture.
		 * @param bottomLeft Bottom left texture coordinates.
		 * @param topRight Top right texture coordinates.
		*/
		SubTexture2D(const Reference<Texture2D>& texture, const Math::Vector2& bottomLeft, const Math::Vector2& topRight);

		/**
		 * @brief Get texture.
		 * @return The texture.
		*/
		const Reference<Texture2D> getTexture() const { return _texture; }

		/**
		 * @brief Get texture coordinates.
		 * @return Texture coords.
		*/
		const Quad::TextureCoordinates getTextureCoords() const { return _texCoords; }

		/**
		 * @brief Create subtexture from its coordinates.
		 * @param texture Source texture.
		 * @param coords Coordinate of the sprite in the spritesheet.
		 * @param cellSize Cell size (sprite size unit).
		 * @param spriteSize Size of the sprite.
		 * @return A new memory managed subtexture.
		*/
		static Reference<SubTexture2D> createFromCoordinates(const Reference<Texture2D>& texture, 
			const Math::Vector2& coords, 
			const Math::Vector2& cellSize, 
			const Math::Vector2& spriteSize = Math::Vector2::one());

	private:

		Reference<Texture2D> _texture;
		Quad::TextureCoordinates _texCoords;

	};

}
