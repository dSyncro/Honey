#include "Application.h"

#include <Honey/Events/EventDispatcher.h>
#include <Honey/Renderer/Renderer.h>

using namespace Honey;

Application* Application::s_Instance = nullptr;

Application::Application()
{
	HNY_PROFILE_FUNCTION();

	HNY_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	_window = Window::Create();
	_window->SetEventCallback(HNY_BIND_EVENT_CALLBACK(Application::OnEvent));

	Renderer::Init();

	_imGuiLayer = new ImGuiLayer();
	PushOverlay(_imGuiLayer);
}

Application::~Application()
{
	HNY_PROFILE_FUNCTION();

	Renderer::Shutdown();
}

void Application::Run()
{
	HNY_PROFILE_FUNCTION();

	_isRunning = true;
	while (_isRunning)
	{
		HNY_PROFILE_SCOPE("Run Loop");
		
		_window->OnUpdate();

		if (!_isMinimized)
		{
			HNY_PROFILE_SCOPE("Layer OnUpdate");
			for (Layer* layer : _layerStack)
				layer->onUpdate();
		}

		_imGuiLayer->begin();
		{
			HNY_PROFILE_SCOPE("Layer OnImGuiRender");
			for (Layer* layer : _layerStack)
				layer->onImGuiRender();
		}
		_imGuiLayer->end();
	}
}

void Application::Close()
{
	_isRunning = false;
}

void Application::PushLayer(Layer* layer)
{
	HNY_PROFILE_FUNCTION();

	_layerStack.pushLayer(layer);
	layer->onAttach();
}

void Application::PushOverlay(Layer* overlay)
{
	HNY_PROFILE_FUNCTION();

	_layerStack.pushOverlay(overlay);
	overlay->onAttach();
}

void Application::OnEvent(Event& e)
{
	HNY_PROFILE_FUNCTION();

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(HNY_BIND_EVENT_CALLBACK(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(Application::OnWindowResize));

	//HNY_CORE_INFO("{0}", e);

	for (std::vector<Layer*>::reverse_iterator it = _layerStack.rbegin(); it != _layerStack.rend(); it++)
	{
		(*it)->onEvent(e);
		if (e.hasBeenHandled) break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	Application::Close();
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	HNY_PROFILE_FUNCTION();

	std::size_t width = e.getSize().Width;
	std::size_t height = e.getSize().Height;

	if (width == 0 || height == 0)
	{
		_isMinimized = true;
		return false;
	}

	_isMinimized = false;
	Renderer::OnWindowResize(width, height);

	return false;
}
