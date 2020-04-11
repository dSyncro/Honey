#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	class HONEY_API KeyReleasedEvent : public KeyEvent {

	public:

		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << _keycode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}