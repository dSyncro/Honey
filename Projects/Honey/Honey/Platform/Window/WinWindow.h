#pragma once

#include <Honey/Logging/Log.h>
#include <Honey/Window/Window.h>

#include <glfw/glfw3.h>

namespace Honey {

	static bool s_isGLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HNY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	class HONEY_API WinWindow : public Window {

	public:

		WinWindow(const WindowProperties& properties);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return _data.Width; }
		inline unsigned int GetHeight() const override { return _data.Height; }

		inline void SetEventCallback(const WindowEventCallback& callback) override { _data.Callback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

		inline void* GetNativeWindow() const override { return _window; }

	private:

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* _window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			WindowEventCallback Callback;
		};

		WindowData _data;
	};

}