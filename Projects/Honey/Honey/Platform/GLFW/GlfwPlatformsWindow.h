#pragma once

#include <Honey/Renderer/GraphicsContext.h>
#include <Honey/Window/Window.h>

extern "C" {
#include <GLFW/glfw3.h>
}


namespace Honey {

	/**
	 * @brief GLFW Window implementation.
	*/
	class GlfwPlatformsWindow : public Window {

	public:

		/**
		 * @brief Construct GlfwPlatformsWindow from its properties.
		 * @param properties The properties.
		*/
		GlfwPlatformsWindow(const WindowProperties& properties);
		virtual ~GlfwPlatformsWindow();

		/**
		 * @brief Called when Window is updated.
		*/
		virtual void onUpdate() override;

		/**
		 * @brief Get window width.
		 * @return The width.
		*/
		UInt getWidth() const override { return _data.width; }

		/**
		 * @brief Get window height.
		 * @return The height.
		*/
		UInt getHeight() const override { return _data.height; }

		/**
		 * @brief Get window size.
		 * @return The size.
		*/
		Math::Size getSize() const override { return { _data.width, _data.height }; }

		/**
		 * @brief Set window event callback.
		 * @param callback New event callback.
		*/
		virtual void setEventCallback(const EventCallback& callback) override { _data.callback = callback; }

		/**
		 * @brief Set window title.
		 * @param title New title.
		*/
		virtual void setTitle(const std::string& title) override;

		/**
		 * @brief Set if VSync is enabled or not.
		 * @param enabled Is VSync enabled?
		*/
		virtual void setVSync(bool enabled) override;

		/**
		 * @brief Check if VSync is enabled.
		*/
		virtual bool isVSyncEnabled() const override;

		/**
		 * @brief Get native underlying window.
		 * @return Native window.
		*/
		void* getNativeWindow() const override { return _window; }

	private:

		/**
		 * @brief Initialize window.
		 * @param properties Window properties.
		*/
		virtual void init(const WindowProperties& properties);

		/**
		 * @brief Shutdown window.
		*/
		virtual void shutdown();

		/**
		 * @brief Poll Events.
		*/
		void pollEvents();

		GLFWwindow* _window;
		Unique<GraphicsContext> _context;

		/**
		 * @brief Window specific data.
		*/
		struct WindowData {
			std::string title = "";
			UInt width = 0, height = 0;
			bool vSync = false;

			EventCallback callback = nullptr;
		};

		WindowData _data;

		/**
		 * @brief Called when window resizes.
		 * @param window The window.
		 * @param width New width.
		 * @param height New height.
		*/
		static void windowResizeCallback(GLFWwindow* window, int width, int height);

		/**
		 * @brief Called when window is about to close.
		 * @param window The window.
		*/
		static void windowCloseCallback(GLFWwindow* window);

		/**
		 * @brief Called when key changes state on window.
		 * @param window The window.
		 * @param key The keycode.
		 * @param scancode The scancode.
		 * @param action The action code.
		 * @param mods Possible mods.
		*/
		static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		 * @brief Called when char is typed.
		 * @param window The window.
		 * @param keycode The char keycode.
		*/
		static void windowCharCallback(GLFWwindow* window, unsigned int keycode);

		/**
		 * @brief Called when mouse button changes state on window.
		 * @param window The window.
		 * @param button The button.
		 * @param action The action code.
		 * @param mods Possible mods.
		*/
		static void windowMouseCallback(GLFWwindow* window, int button, int action, int mods);

		/**
		 * @brief Called on mouse scroll.
		 * @param window The window.
		 * @param xOffset Scroll x-offset.
		 * @param yOffset Scroll y-offset.
		*/
		static void windowScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		/**
		 * @brief Called when mouse position changes.
		 * @param window The window.
		 * @param xPos New X position.
		 * @param yPos New Y position.
		*/
		static void windowCursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	};
}
