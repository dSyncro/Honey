#pragma once

#include <Honey/Renderer/SubTexture.h>
#include <Honey/Renderer/2D/Quad.h>

namespace Honey {

	struct Sprite {

		Sprite(const Reference<Texture2D>& texture = nullptr)
			: Texture(texture), UV(Quad::DefaultTextureCoords) {}

		Sprite(const Reference<SubTexture2D>& subtexture)
			: Texture(subtexture->GetTexture()), UV(subtexture->GetTextureCoords()) {}

		static Reference<Sprite> Create(const Reference<Texture2D>& texture = nullptr) { return CreateReference<Sprite>(texture); }
		static Reference<Sprite> Create(const Reference<SubTexture2D>& subtexture) { return CreateReference<Sprite>(subtexture); }

		Reference<Texture2D> Texture;
		Quad::TextureCoordinates UV;

	};

}
