#include <Honey/Application.h>
#include <Honey/Input/Input.h>

extern "C"{
#include <GLFW/glfw3.h>
}

using namespace Honey;

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

std::pair<float, float> Input::GetMousePosition()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return std::make_pair<float, float>((float)xPos, (float)yPos);
}
