#pragma once

#include <glfw/glfw3.h>

#include <Honey/Renderer/GraphicsContext.h>
#include <Honey/Window/Window.h>


namespace Honey {

	static bool s_isGLFWInitialized = false;

	class HONEY_API WinWindow : public Window {

	public:

		WinWindow(const WindowProperties& properties);
		virtual ~WinWindow();

		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return _data.Width; }
		unsigned int GetHeight() const override { return _data.Height; }

		void SetEventCallback(const WindowEventCallback& callback) override { _data.Callback = callback; }

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;

		void* GetNativeWindow() const override { return _window; }

	private:

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* _window;
		GraphicsContext* _context;

		struct WindowData {
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			WindowEventCallback Callback = nullptr;
		};

		WindowData _data;

		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void WindowCharCallback(GLFWwindow* window, unsigned int keycode);
		static void WindowMouseCallback(GLFWwindow* window, int button, int action, int mods);
		static void WindowScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static void WindowCursorPositionCallback(GLFWwindow* window, double xOffset, double yOffset);
	};

}