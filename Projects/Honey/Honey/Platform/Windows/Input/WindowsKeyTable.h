#pragma once

#include <Honey/Input/Keycode.h>

namespace Honey {

	class WindowsKeyTable {

	public:

		static void Init();

		static Keycode ScancodeToKeycode(uint32_t scancode) { return _keycodes[scancode]; }
		static uint32_t KeycodeToScancode(Keycode keycode) { return _scancodes[(uint32_t)keycode]; }

	private:

		static Keycode _keycodes[512];
		static uint16_t _scancodes[512];
	};

}
