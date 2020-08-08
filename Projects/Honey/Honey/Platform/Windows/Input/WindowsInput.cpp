#include <Honey/Application.h>
#include <Honey/Input/Input.h>

#include "WindowsKeyTable.h"

using namespace Honey;

bool Input::IsKeyPressed(Keycode keycode)
{
	uint16_t scancode = WindowsKeyTable::KeycodeToScancode(keycode);
	UINT vk = MapVirtualKeyA(scancode, MAPVK_VSC_TO_VK_EX);

	return ::GetKeyState(vk) & 0x8000;
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
	UINT vk;
	switch (button)
	{
		case MouseButton::ButtonLeft: vk = VK_LBUTTON; break;
		case MouseButton::ButtonMiddle: vk = VK_MBUTTON; break;
		case MouseButton::ButtonRight: vk = VK_RBUTTON; break;
		case MouseButton::Button4: vk = VK_XBUTTON1; break;
		case MouseButton::Button5: vk = VK_XBUTTON2; break;
		default: HNY_CORE_ASSERT(false, "Unknown Mouse Button!"); return false;
	}
	return ::GetKeyState(vk) & 0x8000;
}

float Input::GetMouseX()
{
	HWND window = static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow());
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(window, &p);
	return (float)p.x;
}

float Input::GetMouseY()
{
	HWND window = static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow());
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(window, &p);
	return (float)p.y;
}

std::pair<float, float> Input::GetMousePosition()
{
	HWND window = static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow());
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(window, &p);
	return std::make_pair<float, float>((float)p.x, (float)p.y);
}

uint16_t Input::GetKeyMods()
{
	uint16_t mods = 0;

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

	return mods;
}

KeyState Input::GetKeyState(Keycode keycode)
{
	return IsKeyPressed(keycode) ? KeyState::Pressed : KeyState::Released;
}

KeyState Input::GetMouseButtonState(MouseButton button)
{
	return IsMouseButtonPressed(button) ? KeyState::Pressed : KeyState::Released;
}
