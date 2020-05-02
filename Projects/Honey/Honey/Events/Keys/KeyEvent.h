#pragma once

#include <Honey/Events/Event.h>
#include <Honey/Input/Keycode.h>

namespace Honey {

	class KeyEvent : public Event {

	public:

		Keycode GetKeyCode() const { return _keycode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		KeyEvent(Keycode keycode) : _keycode(keycode) {}

		Keycode _keycode;
	};

}