#include "Application.h"

#include <Honey/Logging/Log.h>
#include <Honey/Events/EventDispatcher.h>
#include <Honey/Events/Window/WindowResizeEvent.h>
#include <Honey/Renderer/Buffers/BufferLayout.h>
#include <Honey/Renderer/Renderer.h>

using namespace Honey;

Application* Application::s_Instance = nullptr;

Application::Application()
	: _camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	HNY_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	_window = std::unique_ptr<Window>(Window::Create());
	_window->SetEventCallback(HNY_BIND_EVENT_CALLBACK(Application::OnEvent));

	_imGuiLayer = new ImGuiLayer();
	PushOverlay(_imGuiLayer);

	_vertexArray.reset(VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" },
	};

	_vertexBuffer->SetLayout(layout);
	_vertexArray->AddVertexBuffer(_vertexBuffer);

	unsigned int indices[3] = { 0, 1, 2 };

	_indexBuffer.reset(IndexBuffer::Create(indices, 3));
	_vertexArray->SetIndexBuffer(_indexBuffer);

	std::string vertexSource = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;

		out vec3 v_Position;
		out vec4 v_Color;

		void main() {
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSource = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main() {
			color = v_Color;
		}
	)";

	_shader.reset(new Shader(vertexSource, fragmentSource));
}

Application::~Application()
{

}

void Application::Run()
{
	_running = true;
	RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });

	while (_running)
	{
		RenderCommand::Clear();

		_camera.SetPosition({ .5f, .5f, 0.0f });
		_camera.SetRotation(30.0f);

		Renderer::BeginScene(_camera);

		Renderer::Submit(_shader, _vertexArray);

		Renderer::EndScene();

		for (Layer* layer : _layerStack)
			layer->OnUpdate();

		_imGuiLayer->Begin();
		for (Layer* layer : _layerStack)
			layer->OnImGuiRender();
		_imGuiLayer->End();

		_window->OnUpdate();
	}
}

void Application::PushLayer(Layer* layer)
{
	_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay)
{
	_layerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(HNY_BIND_EVENT_CALLBACK(Application::OnWindowClose));

	HNY_CORE_INFO("{0}", e);

	for (auto it = _layerStack.end(); it != _layerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.HasBeenHandled) break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	_running = false;
	return true;
}