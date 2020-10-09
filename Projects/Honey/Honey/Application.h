#pragma once

#include <Honey/Events/WindowEvents.h>
#include <Honey/Layers/LayerStack.h>
#include <Honey/Layers/ImGui/ImGuiLayer.h>
#include <Honey/Window/Window.h>

namespace Honey {

	/**
	 * @brief Application class.
	*/
	class Application
	{
	public:

		Application();
		virtual ~Application();

		/**
		 * @brief Run application.
		*/
		void run();

		/**
		 * @brief Close application.
		*/
		void close();

		/**
		 * @brief Called when events occur.
		 * @param e The event.
		*/
		void onEvent(Event& e);

		/**
		 * @brief Push layer to application.
		 * @param layer The layer.
		*/
		void pushLayer(Layer* layer);

		/**
		 * @brief Push overlay layer to application.
		 * @param overlay The overlay.
		*/
		void pushOverlay(Layer* overlay);

		/**
		 * @brief Set application title.
		 * @param title The title.
		*/
		void setTitle(const std::string& title) { _window->setTitle(title); }

		/**
		 * @brief Get application window.
		 * @return The window.
		*/
		Window& getWindow() { return *_window; }

		/**
		 * @brief Get application.
		 * @return The application.
		*/
		static Application& get() { return *s_Instance; }

	private:

		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

		Unique<Window> _window;
		ImGuiLayer* _imGuiLayer;

		bool _isRunning = false;
		bool _isMinimized = false;
		Float _lastFrameTime = 0.0f;

		LayerStack _layerStack;

		static Application* s_Instance;
	};

	/**
	 * @brief Create application.
	 * Defined by client.
	 * @return Pointer to application.
	*/
	Application* createApplication();

}
