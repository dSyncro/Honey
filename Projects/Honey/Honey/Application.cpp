#include "Application.h"

#include <Honey/Logging/Log.h>
#include <Honey/Events/EventDispatcher.h>
#include <Honey/Events/Window/WindowResizeEvent.h>

using namespace Honey;

#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	_window = std::unique_ptr<Window>(Window::Create());
	_window->SetEventCallback(BIND_EVENT_CALLBACK(OnEvent));
}

Application::~Application()
{

}

void Application::Run()
{
	_running = true;
	while (_running)
	{
		for (Layer* layer : _layerStack)
			layer->OnUpdate();

		_window->OnUpdate();
	}
}

void Application::PushLayer(Layer* layer)
{
	_layerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
	_layerStack.PushOverlay(overlay);
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(OnWindowClose));

	HNY_CORE_TRACE("{0}", e);

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