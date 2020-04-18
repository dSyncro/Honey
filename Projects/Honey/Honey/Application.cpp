#include "Application.h"

#include <Honey/Logging/Log.h>
#include <Honey/Events/EventDispatcher.h>
#include <Honey/Events/Window/WindowResizeEvent.h>

#include <glad/glad.h>

using namespace Honey;

Application* Application::s_Instance = nullptr;

Application::Application()
{
	HNY_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	_window = std::unique_ptr<Window>(Window::Create());
	_window->SetEventCallback(HNY_BIND_EVENT_CALLBACK(Application::OnEvent));

	_imGuiLayer = new ImGuiLayer();
	PushOverlay(_imGuiLayer);

	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	_vertexBuffer->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	unsigned int indices[3] = { 0, 1, 2 };

	_indexBuffer.reset(IndexBuffer::Create(indices, 3));
	_indexBuffer->Bind();

	std::string vertexSource = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;

		out vec3 v_Position;

		void main() {
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSource = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		void main() {
			color = vec4(v_Position * .5 +.5f, 1);
		}
	)";

	_shader.reset(new Shader(vertexSource, fragmentSource));

	glGetError();
}

Application::~Application()
{

}

void Application::Run()
{
	_running = true;
	while (_running)
	{
		glClearColor(.1f, .1f, .1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		_shader->Bind();
		_vertexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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