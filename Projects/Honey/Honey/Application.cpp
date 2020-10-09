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

	// Create window
	_window = Window::create();
	_window->setEventCallback(HNY_BIND_EVENT_CALLBACK(Application::onEvent));

	Renderer::init(); // Init renderer

	_imGuiLayer = new ImGuiLayer();
	pushOverlay(_imGuiLayer);
}

Application::~Application()
{
	HNY_PROFILE_FUNCTION();

	Renderer::shutdown(); // Shutdown renderer
}

void Application::run()
{
	HNY_PROFILE_FUNCTION();

	_isRunning = true;
	while (_isRunning)
	{
		HNY_PROFILE_SCOPE("Run Loop");
		
		// Update window
		_window->onUpdate();

		// Update each layer
		if (!_isMinimized)
		{
			HNY_PROFILE_SCOPE("Layer OnUpdate");
			for (Layer* layer : _layerStack)
				layer->onUpdate();
		}

		// Draw ImGui stuff
		_imGuiLayer->begin();
		{
			HNY_PROFILE_SCOPE("Layer OnImGuiRender");
			for (Layer* layer : _layerStack)
				layer->onImGuiRender();
		}
		_imGuiLayer->end();
	}
}

void Application::close()
{
	_isRunning = false;
}

void Application::pushLayer(Layer* layer)
{
	HNY_PROFILE_FUNCTION();

	_layerStack.pushLayer(layer);
	layer->onAttach();
}

void Application::pushOverlay(Layer* overlay)
{
	HNY_PROFILE_FUNCTION();

	_layerStack.pushOverlay(overlay);
	overlay->onAttach();
}

void Application::onEvent(Event& e)
{
	HNY_PROFILE_FUNCTION();

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(HNY_BIND_EVENT_CALLBACK(Application::onWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(HNY_BIND_EVENT_CALLBACK(Application::onWindowResize));

	//HNY_CORE_INFO("{0}", e);

	// Propagate 
	for (LayerStack::reverse_iterator it = _layerStack.rbegin(); it != _layerStack.rend(); it++)
	{
		(*it)->onEvent(e);
		if (e.hasBeenHandled) break;
	}
}

bool Application::onWindowClose(WindowCloseEvent& e)
{
	Application::close();
	return true;
}

bool Application::onWindowResize(WindowResizeEvent& e)
{
	HNY_PROFILE_FUNCTION();

	UInt width = e.getSize().width;
	UInt height = e.getSize().height;

	if (width == 0 || height == 0)
	{
		_isMinimized = true;
		return false;
	}

	_isMinimized = false;
	Renderer::onWindowResize(width, height);

	return false;
}
