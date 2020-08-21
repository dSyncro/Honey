#pragma once

#include <Honey/Input/Input.h>
#include <Honey/Renderer/GraphicsContext.h>
#include <Honey/Window/Window.h>

#include "TidyException.h"

#define WINDOW_EXCEPTION(hr) WindowsWindow::Exception(__LINE__, __FILE__, hr);

namespace Honey {

	class WindowsWindow : public Window {

	public:

		class Exception : TidyException {

		public:

			Exception(std::size_t line, const char* filename, HRESULT result) noexcept : TidyException(line, filename), _hr(result) {}
			virtual const char* what() const noexcept override;
			virtual const char* GetType() const noexcept override { return "Window Exception"; }

			HRESULT GetErrorCode() const noexcept { return _hr; }
			std::string GetErrorString() const noexcept { return TranslateErrorCode(_hr); }

			static std::string TranslateErrorCode(HRESULT result) noexcept;

		private:

			HRESULT _hr;
		};

		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		uint32_t GetWidth() const override { return _data.Width; }
		uint32_t GetHeight() const override { return _data.Height; }
		Math::Vector2 GetSize() const override { return { (float)_data.Width, (float)_data.Height }; }

		virtual void SetEventCallback(const EventCallback& callback) override { _data.Callback = callback; }

		virtual void SetTitle(const std::string& title) override;

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;

		void* GetNativeWindow() const override { return _window; }

	private:

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		void PollEvents();

		HWND _window;
		Unique<GraphicsContext> _context;

		struct WindowData {
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallback Callback = nullptr;
		};

		class WindowClass {

		public:

			static const char* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;

			static const WindowClass& Get() noexcept
			{
				static WindowClass wndClass;
				return wndClass;
			}

		private:

			WindowClass();
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator =(const WindowClass&) = delete;
			static constexpr const char* _name = "Honey Engine - Direct3D Window";
			HINSTANCE _instance;

		};

		WindowData _data;

		static LRESULT CALLBACK WindowsEventCallbackSetup(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowsEventCallbackThrunk(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

		static void WindowResizeCallback(WindowData& data, int width, int height);
		static void WindowCloseCallback(WindowData& data);
		static void WindowKeyCallback(WindowData& data, Keycode keycode, int scancode, KeyState action, KeyMods mods, int repeat);
		static void WindowCharCallback(WindowData& data, Keycode keycode);
		static void WindowMouseCallback(WindowData& data, MouseButton button, KeyState action, KeyMods mods);
		static void WindowScrollCallback(WindowData& data, double xOffset, double yOffset);
		static void WindowCursorPositionCallback(WindowData& data, double xOffset, double yOffset);
	};

}
