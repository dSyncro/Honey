#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	class KeyReleasedEvent final : public KeyEvent {

	public:

		KeyReleasedEvent(Keycode keycode) : KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}