#pragma once

#include "MouseButtonEvent.h"

namespace Honey {

	class MouseButtonReleasedEvent final : public MouseButtonEvent {

	public:

		MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonReleasedEvent: " << _mouseButton;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}