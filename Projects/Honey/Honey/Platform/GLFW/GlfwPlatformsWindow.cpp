#include "GlfwPlatformsWindow.h"

#include <Honey/Core/Engine.h>
#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>

#include <Honey/Input/Input.h>

using namespace Honey;

// Create Window
Unique<Window> Window::create(const WindowProperties& properties) { return CreateUnique<GlfwPlatformsWindow>(properties); }

GlfwPlatformsWindow::GlfwPlatformsWindow(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();
	
	// Init win
	init(properties);
}

GlfwPlatformsWindow::~GlfwPlatformsWindow()
{
	HNY_PROFILE_FUNCTION();

	// Shutdown win
	shutdown();
}

void GlfwPlatformsWindow::init(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();

	// Setup Window Data
	_data.title = properties.Title;
	_data.width = properties.Width;
	_data.height = properties.Height;

	HNY_CORE_INFO("Creating window {0} ({1}; {2})", properties.Title, properties.Width, properties.Height);

#if defined(HNY_DEBUG)
	if (Renderer::getAPI() == RendererAPI::API::OpenGL)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	_window = glfwCreateWindow(static_cast<int>(_data.width), static_cast<int>(_data.height), _data.title.c_str(), nullptr, nullptr);

	// Init the context
	_context = GraphicsContext::create(_window);
	_context->init();

	// Set window data
	glfwSetWindowUserPointer(_window, &_data);

	// Set window callbacks
	glfwSetWindowSizeCallback  (_window, &GlfwPlatformsWindow::windowResizeCallback        );
	glfwSetWindowCloseCallback (_window, &GlfwPlatformsWindow::windowCloseCallback         );
	glfwSetKeyCallback         (_window, &GlfwPlatformsWindow::windowKeyCallback           );
	glfwSetCharCallback        (_window, &GlfwPlatformsWindow::windowCharCallback          );
	glfwSetMouseButtonCallback (_window, &GlfwPlatformsWindow::windowMouseCallback         );
	glfwSetScrollCallback      (_window, &GlfwPlatformsWindow::windowScrollCallback        );
	glfwSetCursorPosCallback   (_window, &GlfwPlatformsWindow::windowCursorPositionCallback);
}

void GlfwPlatformsWindow::shutdown()
{
	HNY_PROFILE_FUNCTION();

	// Destroy window
	glfwDestroyWindow(_window);
}

void GlfwPlatformsWindow::pollEvents()
{
	Input::mouseScrollAmount() = Math::Vector2(0.0f, 0.0f);
	glfwPollEvents();
}

void GlfwPlatformsWindow::onUpdate()
{
	HNY_PROFILE_FUNCTION();

	pollEvents(); // Poll events
	_context->swapBuffers(); // Good time to swap buffers

	Engine::_timer.markFrame(); // Mark frame
}

void GlfwPlatformsWindow::setTitle(const std::string& title) 
{ 
	_data.title = title; 
	glfwSetWindowTitle(_window, title.c_str()); 
}

void GlfwPlatformsWindow::setVSync(bool enabled)
{
	HNY_PROFILE_FUNCTION();

	glfwSwapInterval(enabled);
	_data.vSync = enabled;
}

bool GlfwPlatformsWindow::isVSyncEnabled() const { return _data.vSync; }

void GlfwPlatformsWindow::windowResizeCallback(GLFWwindow* window, int width, int height)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
	data.width = width;
	data.height = height;

	WindowResizeEvent e(width, height);
	data.callback(e);
}

void GlfwPlatformsWindow::windowCloseCallback(GLFWwindow* window)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
	WindowCloseEvent e = WindowCloseEvent();
	data.callback(e);
}

void GlfwPlatformsWindow::windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	switch (action)
	{
		case GLFW_PRESS:
		{
			KeyPressedEvent e(static_cast<Keycode>(key), 0);
			data.callback(e);
			break;
		}

		case GLFW_RELEASE:
		{
			KeyReleasedEvent e(static_cast<Keycode>(key));
			data.callback(e);
			break;
		}

		case GLFW_REPEAT:
		{
			KeyPressedEvent e(static_cast<Keycode>(key), 1);
			data.callback(e);
			break;
		}
	}
}

void GlfwPlatformsWindow::windowCharCallback(GLFWwindow* window, unsigned int keycode)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
	KeyTypedEvent e(static_cast<Keycode>(keycode));
	data.callback(e);
}

void GlfwPlatformsWindow::windowMouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	switch (action)
	{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent e(static_cast<MouseButton>(button));
			data.callback(e);
			break;
		}

		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent e(static_cast<MouseButton>(button));
			data.callback(e);
			break;
		}
	}
}

void GlfwPlatformsWindow::windowScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	Math::Vector2 offset = Math::Vector2(static_cast<Float>(xOffset), static_cast<Float>(yOffset));
	Input::mouseScrollAmount() = offset;

	MouseScrolledEvent e = MouseScrolledEvent(offset);
	data.callback(e);
}

void GlfwPlatformsWindow::windowCursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	MouseMovedEvent e(static_cast<UInt>(xPos), static_cast<UInt>(yPos));
	data.callback(e);
}
