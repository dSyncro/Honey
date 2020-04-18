#pragma once

#include <Honey/Renderer/GraphicsContext.h>
#include <Honey/Window/Window.h>

#include <glfw/glfw3.h>

namespace Honey {

	static bool s_isGLFWInitialized = false;

	class HONEY_API WinWindow : public Window {

	public:

		WinWindow(const WindowProperties& properties);
		virtual ~WinWindow();

		virtual void OnUpdate() override;

		inline unsigned int GetWidth() const override { return _data.Width; }
		inline unsigned int GetHeight() const override { return _data.Height; }

		inline void SetEventCallback(const WindowEventCallback& callback) override { _data.Callback = callback; }

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;

		inline void* GetNativeWindow() const override { return _window; }

	private:

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* _window;
		GraphicsContext* _context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			WindowEventCallback Callback;
		};

		WindowData _data;
	};

}