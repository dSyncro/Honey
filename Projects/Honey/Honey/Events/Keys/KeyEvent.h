#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API KeyEvent : public Event {

	public:

		int GetKeyCode() const { return _keycode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		KeyEvent(int keycode) : _keycode(keycode) {}

		int _keycode;
	};

}