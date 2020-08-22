#pragma once

#include "Texture.h"

#include <Honey/Math/Vector/Vector2.h>

namespace Honey {

	class SubTexture2D {

	public:

		SubTexture2D(const Reference<Texture2D>& texture, const Math::Vector2& bottomLeft, const Math::Vector2& topRight);

		const Reference<Texture2D> GetTexture() const { return _texture; }
		const std::array<Math::Vector2, 4> GetTextureCoords() const { return _texCoords; }

		static Reference<SubTexture2D> CreateFromCoordinates(const Reference<Texture2D>& texture, 
			const Math::Vector2& coords, 
			const Math::Vector2& cellSize, 
			const Math::Vector2& spriteSize = Math::Vector2::One);

	private:

		Reference<Texture2D> _texture;
		std::array<Math::Vector2, 4> _texCoords;

	};

}
