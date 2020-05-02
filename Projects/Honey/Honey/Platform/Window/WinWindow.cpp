#include "WinWindow.h"

#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>
#include <Honey/Timing/EngineTime.h>

using namespace Honey;

static void GLFWErrorCallback(int error, const char* description)
{
	HNY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
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
	// Setup Window Data
	_data.Title = properties.Title;
	_data.Width = properties.Width;
	_data.Height = properties.Height;

	HNY_CORE_INFO("Creating window {0} ({1}; {2})", properties.Title, properties.Width, properties.Height);

	// Init GLFW if needed
	if (!s_isGLFWInitialized)
	{
		int success = glfwInit();
		HNY_CORE_ASSERT(success, "Could not init GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		s_isGLFWInitialized = true;
	}

	_window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);

	// Init the context
	_context = GraphicsContext::Create(_window);
	_context->Init();

	glfwSetWindowUserPointer(_window, &_data);

#if defined(HNY_DEBUG)
	if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	glfwSetWindowSizeCallback(_window, &WinWindow::WindowResizeCallback);
	glfwSetWindowCloseCallback(_window, &WinWindow::WindowCloseCallback);
	glfwSetKeyCallback(_window, &WinWindow::WindowKeyCallback);
	glfwSetCharCallback(_window, &WinWindow::WindowCharCallback);
	glfwSetMouseButtonCallback(_window, &WinWindow::WindowMouseCallback);
	glfwSetScrollCallback(_window, &WinWindow::WindowScrollCallback);
	glfwSetCursorPosCallback(_window, &WinWindow::WindowCursorPositionCallback);
}

void WinWindow::Shutdown()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void WinWindow::OnUpdate()
{
	glfwPollEvents();
	_context->SwapBuffers();

	EngineTime::SetFrameCount(EngineTime::GetFrameCount() + 1);

	float time = (float)glfwGetTime();
	EngineTime::SetDeltaTime(time - EngineTime::GetTime());
	EngineTime::SetTime(time);
}

void WinWindow::SetVSync(bool enabled)
{
	glfwSwapInterval(enabled);
	_data.VSync = enabled;
}

bool WinWindow::IsVSyncEnabled() const { return _data.VSync; }

void WinWindow::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	data.Width = width;
	data.Height = height;

	WindowResizeEvent e(width, height);
	data.Callback(e);
}

void WinWindow::WindowCloseCallback(GLFWwindow* window)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	WindowCloseEvent e = WindowCloseEvent();
	data.Callback(e);
}

void WinWindow::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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

void WinWindow::WindowCharCallback(GLFWwindow* window, unsigned int keycode)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	KeyTypedEvent e((Keycode)keycode);
	data.Callback(e);
}

void WinWindow::WindowMouseCallback(GLFWwindow* window, int button, int action, int mods)
{
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

void WinWindow::WindowScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	MouseScrolledEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}

void WinWindow::WindowCursorPositionCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	MouseMovedEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}