#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	class HONEY_API KeyPressedEvent : public KeyEvent {

	public:

		KeyPressedEvent(Keycode keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

		int GetRepeatCount() const { return _repeatCount; }

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyPressedEvent: " << _keycode << " (" << _repeatCount << " repeats)";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int _repeatCount;
	};

}