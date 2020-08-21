#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Camera/OrthographicCamera.h"

#include <Honey/Renderer/Shader.h>

namespace Honey {

	class Renderer {

	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const Math::Matrix4x4& transform = Math::Matrix4x4::Identity);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:

		struct SceneData {

			glm::mat4 ViewProjectionMatrix;

		};

		static Unique<SceneData> s_SceneData;
	};

}
