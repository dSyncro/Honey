#pragma once

#include <Honey/Core/Color.h>
#include <Honey/Math/Math.h>

namespace Honey {

	class Quad {

	public:

		struct Vertex {

			Math::Vector3 Position;
			Honey::Color Color;
			Math::Vector2 TexCoord;
			int TextureIndex;
			Math::Vector2 Tiling;

			void Set(
				const Math::Vector3& position = Math::Vector3::Zero, 
				const Honey::Color& color = Color::white(), 
				const Math::Vector2& texCoord = Math::Vector2::zero(), 
				int textureIndex = 0,
				const Math::Vector2& tiling = Math::Vector2::one()
			);

		};

		Quad() = default;
		Quad(const Vertex& first, const Vertex& second, const Vertex& third, const Vertex& forth);

		static constexpr uint32_t VertexCount = 4;

		using TextureCoordinates = std::array<Math::Vector2, VertexCount>;

		static constexpr std::array<Math::Vector3, VertexCount> VertexPositions = {
			Math::Vector3(-0.5f, -0.5f, 0.0f),
			Math::Vector3( 0.5f, -0.5f, 0.0f),
			Math::Vector3( 0.5f,  0.5f, 0.0f),
			Math::Vector3(-0.5f,  0.5f, 0.0f)
		};

		static constexpr TextureCoordinates DefaultTextureCoords = {
			Math::Vector2(0.0f, 0.0f), 
			Math::Vector2(1.0f, 0.0f),
			Math::Vector2(1.0f, 1.0f), 
			Math::Vector2(0.0f, 1.0f)
		};

		Vertex& operator [](int index);
		const Vertex& operator [](int index) const;

		std::array<Vertex, 4> Vertices;
	};

}
