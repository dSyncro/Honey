#pragma once

#include "MouseButtonEvent.h"

namespace Honey {

	/**
	 * @brief Mouse Button Released Event.
	 * Usually occurs when a mouse button gets released.
	*/
	class MouseButtonReleasedEvent final : public MouseButtonEvent {

	public:

		/**
		 * @brief Construct MouseButtonReleasedEvent.
		 * @param button Released mouse button.
		*/
		MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) {}

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonReleasedEvent: " << _mouseButton;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
