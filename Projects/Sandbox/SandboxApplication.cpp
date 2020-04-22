#include <Honey.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ImGui/imgui.h>
#include <Honey/Platform/OpenGL/OpenGLShader.h>

class BaseLayer : public Honey::Layer {

public:

	BaseLayer() : Honey::Layer("Sandbox Layer"), _camera(-1.6f, 1.6f, -0.9f, 0.9f) 
	{
		_vertexArray.reset(Honey::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		Honey::Reference<Honey::VertexBuffer> _vertexBuffer;
		_vertexBuffer.reset(Honey::VertexBuffer::Create(vertices, sizeof(vertices)));

		Honey::BufferLayout layout = {
			{ Honey::ShaderDataType::Float3, "a_Position" },
			{ Honey::ShaderDataType::Float4, "a_Color" },
		};

		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		Honey::Reference<Honey::IndexBuffer> _indexBuffer;
		_indexBuffer.reset(Honey::IndexBuffer::Create(indices, 3));
		_vertexArray->SetIndexBuffer(_indexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(u_Color, 1.0f) * v_Color;
			}
		)";

		_shader.reset(Honey::Shader::Create(vertexSource, fragmentSource));
	}

	virtual void OnUpdate() override
	{
		float deltaTime = Honey::Time::GetDeltaTime();

		HNY_APP_INFO("DeltaTime: {0}", deltaTime);
		HNY_APP_INFO("FPS: {0}", Honey::Time::GetFrameRate());
		HNY_APP_INFO("Frame: {0}", Honey::Time::GetFrameCount());

		// Camera
		if (Honey::Input::IsKeyPressed(Honey::Keycode::A))
			_cameraPosition.x -= _cameraMoveSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::D))
			_cameraPosition.x += _cameraMoveSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::S))
			_cameraPosition.y -= _cameraMoveSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::W))
			_cameraPosition.y += _cameraMoveSpeed * deltaTime;

		// Triangle
		if (Honey::Input::IsKeyPressed(Honey::Keycode::J))
			_trianglePosition.x -= _triangleSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::L))
			_trianglePosition.x += _triangleSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::K))
			_trianglePosition.y -= _triangleSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::I))
			_trianglePosition.y += _triangleSpeed * deltaTime;

		// Camera
		if (Honey::Input::IsKeyPressed(Honey::Keycode::Q))
			_cameraRotation -= _cameraRotationSpeed * deltaTime;
		if (Honey::Input::IsKeyPressed(Honey::Keycode::E))
			_cameraRotation += _cameraRotationSpeed * deltaTime;

		_camera.SetPosition(_cameraPosition);
		_camera.SetRotation(_cameraRotation);

		Honey::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		Honey::RenderCommand::Clear();

		Honey::Renderer::BeginScene(_camera);

		std::dynamic_pointer_cast<Honey::OpenGLShader>(_shader)->SetUniformVec3("u_Color", _triangleColor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _trianglePosition);
		Honey::Renderer::Submit(_shader, _vertexArray, transform);

		Honey::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(_triangleColor));
		ImGui::End();
	}

private:

	Honey::Reference<Honey::Shader> _shader;
	Honey::Reference<Honey::VertexArray> _vertexArray;

	glm::vec3 _cameraPosition = glm::vec3(0, 0, 0);
	float _cameraRotation = 0.0f;
	float _cameraMoveSpeed = 1.0f;
	float _cameraRotationSpeed = 30.0f;

	glm::vec3 _trianglePosition = glm::vec3(0, 0, 0);
	float _triangleSpeed = 0.5f;

	glm::vec3 _triangleColor = glm::vec3(0, 0, 0);

	Honey::OrthographicCamera _camera;
};

class Sandbox : public Honey::Application {

public:

	Sandbox()
	{
		PushLayer(new BaseLayer());
	}

	~Sandbox()
	{

	}
};

Honey::Application* Honey::CreateApplication()
{
	return new Sandbox();
}