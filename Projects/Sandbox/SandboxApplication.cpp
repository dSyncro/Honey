#include <Honey.h>
#include <Honey/Entrypoint.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ImGui/imgui.h>

#include "Sandbox2D.h"

class BaseLayer : public Honey::Layer {

public:

	BaseLayer() : Honey::Layer("Sandbox Layer"), _cameraController(16.0f, 9.0f) 
	{
		_vertexArray = Honey::VertexArray::Create();

		const unsigned int vertexCount = 4;
		const unsigned int bufferStride = 5;
		float vertices[vertexCount * bufferStride] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Honey::Reference<Honey::VertexBuffer> _vertexBuffer;
		_vertexBuffer = Honey::VertexBuffer::Create(vertices, sizeof(vertices));

		Honey::BufferLayout layout = {
			{ Honey::ShaderDataType::Float3, "a_Position" },
			{ Honey::ShaderDataType::Float2, "a_TexCoord" },
		};

		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[3 * 2] = { 0, 1, 2, 2, 3, 0 };

		Honey::Reference<Honey::IndexBuffer> _indexBuffer;
		_indexBuffer = Honey::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		_vertexArray->SetIndexBuffer(_indexBuffer);
		
		Honey::Reference<Honey::Shader> textureShader = _shaderLib.Load("assets/shaders/texture.glsl");

		_texture = Honey::Texture2D::Create("assets/textures/checkerboard.png");
		_transparentTexture = Honey::Texture2D::Create("assets/textures/logo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

	}

	virtual void OnUpdate() override
	{
		float deltaTime = Honey::Time::GetDeltaTime();

		HNY_APP_INFO("DeltaTime: {0}", deltaTime);
		HNY_APP_INFO("FPS: {0}", Honey::Time::GetFrameRate());
		HNY_APP_INFO("Frame: {0}", Honey::Time::GetFrameCount());

		_cameraController.OnUpdate();

		// Square
		if (Honey::Input::IsKeyPressed(Honey::Keycode::J))
			_squarePosition.x -= _squareSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::L))
			_squarePosition.x += _squareSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::K))
			_squarePosition.y -= _squareSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::I))
			_squarePosition.y += _squareSpeed * deltaTime;

		Honey::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		Honey::RenderCommand::Clear();

		Honey::Renderer::BeginScene(_cameraController.GetCamera());

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _squarePosition);

		Honey::Reference<Honey::Shader> textureShader = _shaderLib.Get("texture");

		_texture->Bind();
		Honey::Renderer::Submit(textureShader, _vertexArray, transform);

		transform = glm::translate(transform, glm::vec3(0.25f));
		_transparentTexture->Bind();
		Honey::Renderer::Submit(textureShader, _vertexArray, transform);

		Honey::Renderer::EndScene();
	}

	virtual void OnEvent(Honey::Event& e)
	{
		_cameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(_squareColor));
		ImGui::End();
	}

private:

	Honey::ShaderLibrary _shaderLib;

	Honey::Reference<Honey::VertexArray> _vertexArray;

	Honey::Reference<Honey::Texture2D> _texture;
	Honey::Reference<Honey::Texture2D> _transparentTexture;

	glm::vec3 _squarePosition = glm::vec3(0, 0, 0);
	float _squareSpeed = 0.5f;
	glm::vec3 _squareColor = glm::vec3(0, 0, 0);

	Honey::OrthographicCameraController _cameraController;
};

class Sandbox : public Honey::Application {

public:

	Sandbox()
	{
		// PushLayer(new BaseLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() = default;
};

Honey::Application* Honey::CreateApplication()
{
	return new Sandbox();
}