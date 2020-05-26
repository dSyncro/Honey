#pragma once

#include <glm/glm.hpp>

namespace Honey {

	class Quad {

	public:

		struct Vertex {

			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TexCoord;
			float TextureIndex;

			void Set(
				const glm::vec3& position = glm::vec3(0.0f), 
				const glm::vec4& color = glm::vec4(1.0f), 
				const glm::vec2& texCoord = glm::vec2(0.0f), 
				float textureIndex = 0.0f
			);

		};

		Quad() = default;
		Quad(const Vertex& first, const Vertex& second, const Vertex& third, const Vertex& forth);

		static constexpr uint32_t VertexCount = 4;
		static constexpr glm::vec2 TextureCoords[VertexCount] = {
			{ 0.0f, 0.0f }, { 1.0f, 0.0f },
			{ 1.0f, 1.0f }, { 0.0f, 1.0f }
		};

		Vertex& operator [](int index);
		const Vertex& operator [](int index) const;

		Vertex Vertices[4];
	};

}