#pragma once

#include "Texture.h"

#include <Honey/Math/Vector/Vector2.h>
#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	class SubTexture2D {

	public:

		SubTexture2D(const Reference<Texture2D>& texture, const Math::Vector2& bottomLeft, const Math::Vector2& topRight);

		const Reference<Texture2D> GetTexture() const { return _texture; }
		const Quad::TextureCoordinates GetTextureCoords() const { return _texCoords; }

		static Reference<SubTexture2D> CreateFromCoordinates(const Reference<Texture2D>& texture, 
			const Math::Vector2& coords, 
			const Math::Vector2& cellSize, 
			const Math::Vector2& spriteSize = Math::Vector2::one());

	private:

		Reference<Texture2D> _texture;
		Quad::TextureCoordinates _texCoords;

	};

}
