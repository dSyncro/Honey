#pragma once

#include <Honey/Core/MemoryManagement.h>

#include "Keycode.h"
#include "MouseButtons.h"

namespace Honey {

	class Input {

	public:

		Input(const Input&) = delete;
		Input& operator =(const Input&) = delete;

		static bool IsKeyPressed(Keycode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseButton button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:

		Input() = default;

		virtual bool IsKeyPressedImpl(Keycode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:

		static Unique<Input> s_Instance;
	};

}