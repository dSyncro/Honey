#pragma once

#include <sstream>

#include "KeyEvent.h"

namespace Honey {

	/**
	 * @brief Key Pressed event.
	 * Usually occurs when a keyboard keydown stroke is captured.
	*/
	class KeyPressedEvent final : public KeyEvent {

	public:

		/**
		 * @brief Construct KeyPressedEvent.
		 * @param keycode Pressed keycode.
		 * @param repeatCount Repeat count.
		*/
		KeyPressedEvent(Keycode keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

		/**
		 * @brief Get the number of times the keystroke is autorepeated 
		 * as a result of the user holding down the key.
		 * @return The repeat count.
		*/
		int getRepeatCount() const { return _repeatCount; }

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
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
