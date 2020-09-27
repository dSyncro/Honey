#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	/**
	 * @brief Key Typed Event.
	 * This is a particular kind of key event
	 * that usually occurs when you actually type
	 * a printable character.
	*/
	class KeyTypedEvent final : public KeyEvent {

	public:

		KeyTypedEvent(Keycode keycode) : KeyEvent(keycode) {}

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "KeyTypedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}
