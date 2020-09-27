#pragma once

#include <Honey/Events/Event.h>
#include <Honey/Input/Keycode.h>

namespace Honey {

	/**
	 * @brief Base class for Key events.
	 * Key events are events that in some kind of
	 * form are related to keyboard input.
	*/
	class KeyEvent : public Event {

	public:

		/**
		 * @brief Get event keycode.
		 * @return Event keycode.
		*/
		Keycode getKeyCode() const { return _keycode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		/**
		 * @brief Only derived classes can instance KeyEvents.
		*/
		KeyEvent(Keycode keycode) : _keycode(keycode) {}

		Keycode _keycode;
	};

}
