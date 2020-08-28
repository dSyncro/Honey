#include "GlfwPlatformsWindow.h"

#include <Honey/Core/Engine.h>
#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>

#include <Honey/Input/Input.h>

using namespace Honey;

Unique<Window> Window::Create(const WindowProperties& properties) { return CreateUnique<GlfwPlatformsWindow>(properties); }

GlfwPlatformsWindow::GlfwPlatformsWindow(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();
	
	Init(properties);
}

GlfwPlatformsWindow::~GlfwPlatformsWindow()
{
	HNY_PROFILE_FUNCTION();

	Shutdown();
}

void GlfwPlatformsWindow::Init(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();

	// Setup Window Data
	_data.Title = properties.Title;
	_data.Width = properties.Width;
	_data.Height = properties.Height;

	HNY_CORE_INFO("Creating window {0} ({1}; {2})", properties.Title, properties.Width, properties.Height);

#if defined(HNY_DEBUG)
	if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	_window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);

	// Init the context
	_context = GraphicsContext::Create(_window);
	_context->Init();

	glfwSetWindowUserPointer(_window, &_data);

	glfwSetWindowSizeCallback  (_window, &GlfwPlatformsWindow::WindowResizeCallback        );
	glfwSetWindowCloseCallback (_window, &GlfwPlatformsWindow::WindowCloseCallback         );
	glfwSetKeyCallback         (_window, &GlfwPlatformsWindow::WindowKeyCallback           );
	glfwSetCharCallback        (_window, &GlfwPlatformsWindow::WindowCharCallback          );
	glfwSetMouseButtonCallback (_window, &GlfwPlatformsWindow::WindowMouseCallback         );
	glfwSetScrollCallback      (_window, &GlfwPlatformsWindow::WindowScrollCallback        );
	glfwSetCursorPosCallback   (_window, &GlfwPlatformsWindow::WindowCursorPositionCallback);
}

void GlfwPlatformsWindow::Shutdown()
{
	HNY_PROFILE_FUNCTION();

	glfwDestroyWindow(_window);
}

void GlfwPlatformsWindow::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	Input::MouseScrollAmount() = Math::Vector2(0.0f, 0.0f);
	glfwPollEvents();
	_context->SwapBuffers();

	Engine::_timer.MarkFrame();
}

void GlfwPlatformsWindow::SetTitle(const std::string& title) 
{ 
	_data.Title = title; 
	glfwSetWindowTitle(_window, title.c_str()); 
}

void GlfwPlatformsWindow::SetVSync(bool enabled)
{
	HNY_PROFILE_FUNCTION();

	glfwSwapInterval(enabled);
	_data.VSync = enabled;
}

bool GlfwPlatformsWindow::IsVSyncEnabled() const { return _data.VSync; }

void GlfwPlatformsWindow::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	data.Width = width;
	data.Height = height;

	WindowResizeEvent e(width, height);
	data.Callback(e);
}

void GlfwPlatformsWindow::WindowCloseCallback(GLFWwindow* window)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	WindowCloseEvent e = WindowCloseEvent();
	data.Callback(e);
}

void GlfwPlatformsWindow::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void GlfwPlatformsWindow::WindowCharCallback(GLFWwindow* window, unsigned int keycode)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	KeyTypedEvent e((Keycode)keycode);
	data.Callback(e);
}

void GlfwPlatformsWindow::WindowMouseCallback(GLFWwindow* window, int button, int action, int mods)
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

void GlfwPlatformsWindow::WindowScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Input::MouseScrollAmount() = Math::Vector2((float)xOffset, (float)yOffset);
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	MouseScrolledEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}

void GlfwPlatformsWindow::WindowCursorPositionCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	MouseMovedEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}
