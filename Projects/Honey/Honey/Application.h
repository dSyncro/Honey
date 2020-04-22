#pragma once

#include "Core.h"

#include <Honey/Events/WindowEvents.h>
#include <Honey/Layers/LayerStack.h>
#include <Honey/Layers/ImGui/ImGuiLayer.h>
#include <Honey/Renderer/OrthographicCamera.h>
#include <Honey/Renderer/VertexArray.h>
#include <Honey/Renderer/Buffers/VertexBuffer.h>
#include <Honey/Renderer/Buffers/IndexBuffer.h>
#include <Honey/Renderer/Shader.h>
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

		inline Window& GetWindow() { return *_window; }

		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		ImGuiLayer* _imGuiLayer;

		bool _running = false;
		float _lastFrameTime = 0.0f;

		LayerStack _layerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}