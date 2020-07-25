#pragma once

#include <Honey/Core/MemoryManagement.h>

#include "Keycode.h"
#include "MouseButtons.h"

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
		static std::pair<float, float> GetMousePosition();
	};

}