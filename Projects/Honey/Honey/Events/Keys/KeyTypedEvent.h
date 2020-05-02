#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	class KeyTypedEvent final : public KeyEvent {

	public:

		KeyTypedEvent(Keycode keycode) : KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyTypedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}