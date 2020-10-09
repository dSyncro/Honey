#include <Honey/Application.h>
#include <Honey/Input/Input.h>

extern "C"{
#include <GLFW/glfw3.h>
}

using namespace Honey;
using namespace Honey::Math;

bool Input::isKeyPressed(Keycode keycode)
{
	// Is key pressed or repeated on window?

	GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
	int state = glfwGetKey(window, static_cast<int>(keycode));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMousePressed(MouseButton button)
{
	// Is button pressed or repeated on window?

	GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
	int state = glfwGetMouseButton(window, static_cast<int>(button));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float Input::getMouseX()
{
	// Get cursor position
	Vector2 pos = getMousePosition();
	return pos.x; // return x component only.
}

float Input::getMouseY()
{
	// Get cursor position
	Vector2 pos = getMousePosition();
	return pos.y; // return y component only.
}

Vector2 Input::getMousePosition()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return Vector2(static_cast<float>(xPos), static_cast<float>(yPos));
}

float Input::getVMouseScroll() { return mouseScrollAmount().y; }
float Input::getHMouseScroll() { return mouseScrollAmount().x; }

uint16_t Input::getKeyMods()
{
	uint16_t mods = 0;

	/*
	if (::GetKeyState(VK_SHIFT) & 0x8000)
		mods |= KeyMods::Shift;
	if (::GetKeyState(VK_CONTROL) & 0x8000)
		mods |= KeyMods::Control;
	if (::GetKeyState(VK_MENU) & 0x8000)
		mods |= KeyMods::Alt;
	if ((::GetKeyState(VK_LWIN) | ::GetKeyState(VK_RWIN)) & 0x8000)
		mods |= KeyMods::Super;
	if (::GetKeyState(VK_CAPITAL) & 1)
		mods |= KeyMods::CapsLock;
	if (::GetKeyState(VK_NUMLOCK) & 1)
		mods |= KeyMods::NumLock;
	*/

	return mods;
}

KeyState Input::getKeyState(Keycode keycode)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
	int state = glfwGetKey(window, static_cast<int>(keycode));
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}

KeyState Input::getMouseButtonState(MouseButton button)
{
	GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
	int state = glfwGetMouseButton(window, static_cast<int>(button));
	return state == GLFW_RELEASE ? KeyState::Pressed : KeyState::Released;
}
