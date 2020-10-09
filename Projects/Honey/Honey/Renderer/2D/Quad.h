#pragma once

#include <Honey/Core/Color.h>
#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Drawable quad representation.
	*/
	class Quad {

	public:

		/**
		 * @brief Quad Vertex.
		*/
		struct Vertex {

			/** @brief Vertex position. */
			Math::Vector3 position;

			/** @brief Vertex color. */
			Color color;

			/** @brief Vertex texture coordinates. */
			Math::Vector2 texCoord;

			/** @brief Vertex texture index. */
			Int textureIndex;

			/** @brief Vertex tiling. */
			Math::Vector2 tiling;

			/**
			 * @brief Set vertex values.
			 * @param position New position.
			 * @param color New color.
			 * @param texCoord New texture coords.
			 * @param textureIndex New texture index.
			 * @param tiling New tiling.
			*/
			void Set(
				const Math::Vector3& position = Math::Vector3::zero(), 
				const Color& color = Color::white(), 
				const Math::Vector2& texCoord = Math::Vector2::zero(), 
				Int textureIndex = 0,
				const Math::Vector2& tiling = Math::Vector2::one()
			);

		};

		Quad() = default;

		/**
		 * @brief Construct Quad from vertices.
		 * @param first First vertex.
		 * @param second Second vertex.
		 * @param third Third vertex.
		 * @param forth Fourth vertex.
		*/
		Quad(const Vertex& first, const Vertex& second, const Vertex& third, const Vertex& forth);

		/** @brief Quad vertex count. */
		static constexpr UShort VertexCount = 4;

		/** @brief Quad texture coordinates type. */
		using TextureCoordinates = std::array<Math::Vector2, VertexCount>;

		/** @brief Quad default vertices position. */
		static constexpr std::array<Math::Vector3, VertexCount> VertexPositions = {
			Math::Vector3(-0.5f, -0.5f, 0.0f),
			Math::Vector3( 0.5f, -0.5f, 0.0f),
			Math::Vector3( 0.5f,  0.5f, 0.0f),
			Math::Vector3(-0.5f,  0.5f, 0.0f)
		};

		/** @brief Quad default texture coordinates. */
		static constexpr TextureCoordinates DefaultTextureCoords = {
			Math::Vector2(0.0f, 0.0f), 
			Math::Vector2(1.0f, 0.0f),
			Math::Vector2(1.0f, 1.0f), 
			Math::Vector2(0.0f, 1.0f)
		};

		/**
		 * @brief Retrieve vertex at index.
		 * @param index The index.
		 * @return The vertex at index.
		*/
		Vertex& operator [](Int index);

		/**
		 * @brief Retrieve vertex at index (const version).
		 * @param index The index.
		 * @return The vertex at index.
		*/
		const Vertex& operator [](Int index) const;

		/** @brief Quad vertices. */
		std::array<Vertex, VertexCount> Vertices;
	};

}
