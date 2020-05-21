#pragma once

#include "Texture.h"
#include "Camera/OrthographicCamera.h"

namespace Honey {

	class Renderer2D {

	public:

		static void Init();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void Shutdown();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture);
	};

}