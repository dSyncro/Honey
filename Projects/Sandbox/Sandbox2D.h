#pragma once

#include <Honey.h>

class Sandbox2D : public Honey::Layer {

public:

	Sandbox2D() : Honey::Layer("Sandbox 2D Layer"), _cameraController(1.6f, 0.9f) {}
	~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Honey::Event& e) override;
	virtual void OnImGuiRender() override;

private:

	Honey::Reference<Honey::VertexArray> _vertexArray;

	Honey::ShaderLibrary _shaderLib;
	Honey::OrthographicCameraController _cameraController;

	glm::vec4 _squareColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};