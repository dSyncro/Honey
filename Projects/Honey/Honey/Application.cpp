#include "Application.h"

#include <Honey/Logging/Log.h>
#include <Honey/Events/EventDispatcher.h>
#include <Honey/Events/Window/WindowResizeEvent.h>
#include <Honey/Renderer/Buffers/BufferLayout.h>
#include <Honey/Renderer/Renderer.h>

using namespace Honey;

Application* Application::s_Instance = nullptr;

Application::Application()
{
	HNY_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	_window = std::unique_ptr<Window>(Window::Create());
	_window->SetEventCallback(HNY_BIND_EVENT_CALLBACK(Application::OnEvent));
	_window->SetVSync(false);

	Renderer::Init();

	_imGuiLayer = new ImGuiLayer();
	PushOverlay(_imGuiLayer);
}

Application::~Application()
{

}

void Application::Run()
{
	_isRunning = true;

	while (_isRunning)
	{
		_window->OnUpdate();

		if (!_isMinimized)
		{
			for (Layer* layer : _layerStack)
				layer->OnUpdate();
		}

		_imGuiLayer->Begin();
		for (Layer* layer : _layerStack)
			layer->OnImGuiRender();
		_imGuiLayer->End();

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
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(Application::OnWindowResize));

	HNY_CORE_INFO("{0}", e);

	for (auto it = _layerStack.end(); it != _layerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.HasBeenHandled) break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	_isRunning = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	uint32_t width = e.GetWidth();
	uint32_t height = e.GetHeight();

	if (width == 0 || height == 0)
	{
		_isMinimized = true;
		return false;
	}

	_isMinimized = false;
	Renderer::OnWindowResize(width, height);

	return false;
}