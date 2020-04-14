#include "WinWindow.h"

#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Logging/Log.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>

using namespace Honey;

Window* Window::Create(const WindowProperties& properties)
{
	return new WinWindow(properties);
}

WinWindow::WinWindow(const WindowProperties& properties)
{
	Init(properties);
}

WinWindow::~WinWindow()
{
	Shutdown();
}

void WinWindow::Init(const WindowProperties& properties)
{
	_data.Title = properties.Title;
	_data.Width = properties.Width;
	_data.Height = properties.Height;

	HNY_CORE_INFO("Creating window {0} ({1}; {2})", properties.Title, properties.Width, properties.Height);

	if (!s_isGLFWInitialized)
	{
		int success = glfwInit();
		HNY_CORE_ASSERT(success, "Could not init GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		s_isGLFWInitialized = true;
	}

	_window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);

	_context = new OpenGLContext(_window);
	_context->Init();

	glfwSetWindowUserPointer(_window, &_data);

	SetVSync(true);

	glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent e(width, height);
		data.Callback(e);
		}
	);

	glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent e = WindowCloseEvent();
		data.Callback(e);
		}
	);

	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent e((Keycode)key, 0);
				data.Callback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent e((Keycode)key);
				data.Callback(e);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent e((Keycode)key, 1);
				data.Callback(e);
				break;
			}
		}
		}
	);

	glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent e((Keycode)keycode);
		data.Callback(e);
		}
	);

	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e((MouseButton)button);
				data.Callback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e((MouseButton)button);
				data.Callback(e);
				break;
			}
		}
		}
	);

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent e((float)xOffset, (float)yOffset);
		data.Callback(e);
		}
	);

	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent e((float)xOffset, (float)yOffset);
		data.Callback(e);
		}
	);
}

void WinWindow::Shutdown()
{
	glfwDestroyWindow(_window);
}

void WinWindow::OnUpdate()
{
	glfwPollEvents();
	_context->SwapBuffers();
}

void WinWindow::SetVSync(bool enabled)
{
	glfwSwapInterval(enabled);
	_data.VSync = enabled;
}

bool WinWindow::IsVSyncEnabled() const { return _data.VSync; }