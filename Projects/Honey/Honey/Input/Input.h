#pragma once

#include <Honey/Core.h>

#include "Keycode.h"
#include "MouseButtons.h"

namespace Honey {

	class HONEY_API Input {

	public:

		static bool IsKeyPressed(Keycode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseButton button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:

		virtual bool IsKeyPressedImpl(Keycode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:

		static Input* s_Instance;
	};

}