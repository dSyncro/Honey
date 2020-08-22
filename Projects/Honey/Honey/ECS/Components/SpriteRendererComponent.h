#pragma once

#include <Honey/Renderer/2D/Quad.h>
#include <Honey/Renderer/SubTexture.h>
#include <Honey/Math/Vectors.h>

namespace Honey {

	struct SpriteRendererComponent {
		
		SpriteRendererComponent(const Reference<Texture2D> texture = nullptr, const Math::Vector4& tint = Math::Vector4::One)
			: Texture(texture), UV(Quad::TextureCoords), Tint(tint) {}

		SpriteRendererComponent(const Reference<SubTexture2D> subtexture, const Math::Vector4& tint = Math::Vector4::One)
			: Texture(subtexture->GetTexture()), UV(subtexture->GetTextureCoords()), Tint(tint) {}

		~SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;

		Reference<Texture2D> Texture;
		std::array<Math::Vector2, 4> UV;
		Math::Vector4 Tint;
	};

}
