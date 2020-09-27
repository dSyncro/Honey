#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	/**
	 * @brief Key Released event.
	 * Usually occurs when a keyboard keyup stroke is captured.
	*/
	class KeyReleasedEvent final : public KeyEvent {

	public:

		KeyReleasedEvent(Keycode keycode) : KeyEvent(keycode) {}

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
