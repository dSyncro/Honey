#pragma once

#include "MouseButtonEvent.h"

namespace Honey {

	/**
	 * @brief Mouse Button Pressed Event.
	 * Usually occurs when a mouse button is pressed.
	*/
	class MouseButtonPressedEvent final : public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonPressedEvent: " << _mouseButton;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

}
