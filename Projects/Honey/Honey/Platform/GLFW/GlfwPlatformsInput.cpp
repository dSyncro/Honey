#include <Honey/Application.h>
#include <Honey/Input/Input.h>

extern "C"{
#include <GLFW/glfw3.h>
}

using namespace Honey;
using namespace Honey::Math;

bool Input::isKeyPressed(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, (int)keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMousePressed(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float Input::getMouseX()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)xPos;
}

float Input::getMouseY()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)yPos;
}

Vector2 Input::getMousePosition()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return Vector2((float)xPos, (float)yPos);
}

float Input::getVMouseScroll() { return mouseScrollAmount().y; }
float Input::getHMouseScroll() { return mouseScrollAmount().x; }

uint16_t Input::getKeyMods()
{
	return 0;
}

KeyState Input::getKeyState(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, (int)keycode);
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}

KeyState Input::getMouseButtonState(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}
