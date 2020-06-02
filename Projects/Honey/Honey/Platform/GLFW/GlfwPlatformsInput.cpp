#include "GlfwPlatformsInput.h"

#include <Honey/Application.h>

extern "C"{
#include <GLFW/glfw3.h>
}

using namespace Honey;

Unique<Input> Input::s_Instance = CreateUnique<GlfwPlatformsInput>();

bool GlfwPlatformsInput::IsKeyPressedImpl(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, (int)keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool GlfwPlatformsInput::IsMouseButtonPressedImpl(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float GlfwPlatformsInput::GetMouseXImpl()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)xPos;
}

float GlfwPlatformsInput::GetMouseYImpl()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)yPos;
}
