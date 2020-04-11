#pragma once

#include "MouseButtonEvent.h"

namespace Honey {

	class HONEY_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:

		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonReleasedEvent: " << _mouseButton;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}