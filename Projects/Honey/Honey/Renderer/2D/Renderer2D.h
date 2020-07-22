#pragma once

#include <Honey/Renderer/Texture.h>
#include <Honey/Renderer/Camera/OrthographicCamera.h>

namespace Honey {

	class Renderer2D {

	public:

		struct Statistics {

			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTriangleCount() const { return QuadCount * 2; }
			uint32_t GetVertexCount() const { return QuadCount * 4; }
			uint32_t GetIndexCount() const { return QuadCount * 6; }

			void Reset() { DrawCalls = 0; QuadCount = 0; }

		};

		static void Init();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void NewBatch();
		static void Flush();

		static void Shutdown();

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Reference<Texture2D>& texture, glm::vec2 tiling = glm::vec2(1.0f, 1.0f));

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture, glm::vec2 tiling = glm::vec2(1.0f, 1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture, glm::vec2 tiling = glm::vec2(1.0f, 1.0f));

		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Reference<Texture2D>& texture, glm::vec2 tiling = glm::vec2(1.0f, 1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Reference<Texture2D>& texture, glm::vec2 tiling = glm::vec2(1.0f, 1.0f));

		static void ResetStatistics();
		static const Statistics& GetStatistics();

	private:

		static void FlushAndReset();
	};

}