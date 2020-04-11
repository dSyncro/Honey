#pragma once

#include "Core.h"

#include <Honey/Events/WindowEvents.h>
#include <Honey/Layer/LayerStack.h>
#include <Honey/Window/Window.h>

namespace Honey {

	class HONEY_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = false;

		LayerStack _layerStack;
	};

	Application* CreateApplication();

}