#pragma once

#include "MouseButtonEvent.h"

namespace Honey {

	class HONEY_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonPressedEvent: " << _mouseButton;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

}