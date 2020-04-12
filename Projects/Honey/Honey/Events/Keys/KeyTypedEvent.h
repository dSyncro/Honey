#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	class HONEY_API KeyTypedEvent : public KeyEvent {

	public:

		KeyTypedEvent(Keycode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyTypedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}