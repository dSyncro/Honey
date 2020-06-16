#pragma once

#include <Honey.h>

namespace Honey {

	class EditorLayer : public Honey::Layer {

	public:

		EditorLayer() : Layer("Editor Layer"), _cameraController(1.6f, 0.9f) {}
		~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

	private:

		Reference<VertexArray> _vertexArray;
		Reference<Texture2D> _texture;
		Reference<FrameBuffer> _frameBuffer;

		ShaderLibrary _shaderLib;
		OrthographicCameraController _cameraController;

		Math::Vector2 _viewportSize;
		glm::vec4 _squareColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	};
}