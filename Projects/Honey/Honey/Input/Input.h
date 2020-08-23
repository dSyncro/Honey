#pragma once

#include "Keycode.h"
#include "MouseButtons.h"
#include "KeyMods.h"
#include "KeyState.h"

#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Vector/Vector2.h>

namespace Honey {

	class Input {

	public:

		Input() = delete;
		Input(const Input&) = delete;
		Input& operator =(const Input&) = delete;

		static bool IsKeyPressed(Keycode keycode);
		static bool IsMouseButtonPressed(MouseButton button);
		static float GetMouseX();
		static float GetMouseY();
		static Math::Vector2 GetMousePosition();
		static float GetMouseScroll();
		static float GetHorizontalMouseScroll();
		static uint16_t GetKeyMods();
		static KeyState GetKeyState(Keycode keycode);
		static KeyState GetMouseButtonState(MouseButton button);

	private:

		// TODO: Improve Input Polling situation

		static Math::Vector2& MouseScrollAmount() { static Math::Vector2 scroll; return scroll; }

		friend class GlfwPlatformsWindow;
	};

}
