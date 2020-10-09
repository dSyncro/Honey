#pragma once

#include <Honey/Renderer/SubTexture.h>
#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	/**
	 * @brief Sprite API.
	*/
	struct Sprite {

		/**
		 * @brief Construct sprite from texture.
		 * @param texture The texture.
		*/
		Sprite(const Reference<Texture2D>& texture = nullptr)
			: texture(texture), uv(Quad::DefaultTextureCoords) {}

		/**
		 * @brief Construct sprite from subtexture.
		 * @param subtexture The subtexture.
		*/
		Sprite(const Reference<SubTexture2D>& subtexture)
			: texture(subtexture->getTexture()), uv(subtexture->getTextureCoords()) {}

		/**
		 * @brief Create a new sprite.
		 * @param texture Sprite texture.
		 * @return A new memory managed sprite.
		*/
		static Reference<Sprite> create(const Reference<Texture2D>& texture = nullptr) { return CreateReference<Sprite>(texture); }

		/**
		 * @brief Create a new sprite.
		 * @param subtexture Sprite subtexture.
		 * @return A new memory managed sprite.
		*/
		static Reference<Sprite> create(const Reference<SubTexture2D>& subtexture) { return CreateReference<Sprite>(subtexture); }

		/** @brief Sprite texture. */
		Reference<Texture2D> texture;

		/** @brief Sprite texture coordinates. */
		Quad::TextureCoordinates uv;

	};

}
