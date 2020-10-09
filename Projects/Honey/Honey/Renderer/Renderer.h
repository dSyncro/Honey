#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Camera/OrthographicCamera.h"

#include <Honey/Renderer/Shader.h>

namespace Honey {

	/**
	 * @brief Base 3D Renderer.
	*/
	class Renderer {

	public:

		/**
		 * @brief Initialize renderer.
		*/
		static void init();

		/**
		 * @brief Shutdown renderer. 
		 * Release all related resources.
		*/
		static void shutdown();

		/**
		 * @brief Begin scene rendering.
		 * @param camera Render camera.
		*/
		static void beginScene(OrthographicCamera& camera);

		/**
		 * @brief End scene rendering.
		*/
		static void endScene();

		/**
		 * @brief Submit to renderer.
		 * @param shader Shader.
		 * @param vertexArray Vertex Array.
		 * @param transform Transformation to apply.
		*/
		static void submit(
			const Reference<Shader>& shader,
			const Reference<VertexArray>& vertexArray, 
			const Math::Matrix4x4& transform = Math::Matrix4x4::identity()
		);

		/**
		 * @brief Get current rendering API.
		 * @return Rendering API.
		*/
		static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

		/**
		 * @brief Called when window resize.
		 * @param width New window width.
		 * @param height New window height.
		*/
		static void onWindowResize(UInt width, UInt height);

	private:

		struct SceneData {

			Math::Matrix4x4 viewProjectionMatrix;

		};

		static Unique<SceneData> s_SceneData;
	};
}
