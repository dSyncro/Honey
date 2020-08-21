#include <Honey/Application.h>
#include <Honey/Input/Input.h>

extern "C"{
#include <GLFW/glfw3.h>
}

using namespace Honey;
using namespace Honey::Math;

bool Input::IsKeyPressed(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, (int)keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float Input::GetMouseX()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)xPos;
}

float Input::GetMouseY()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return (float)yPos;
}

Vector2 Input::GetMousePosition()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return Vector2((float)xPos, (float)yPos);
}

float Input::GetMouseScroll() { return MouseScrollAmount().Y; }
float Input::GetHorizontalMouseScroll() { return MouseScrollAmount().X; }

uint16_t Input::GetKeyMods()
{
	return 0;
}

KeyState Input::GetKeyState(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, (int)keycode);
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}

KeyState Input::GetMouseButtonState(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, (int)button);
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}
