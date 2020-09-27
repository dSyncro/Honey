#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

#include <Honey/Input/MouseButtons.h>

namespace Honey {

	/**
	 * @brief Base class for Mouse Buttons events.
	*/
	class MouseButtonEvent : public Event {

	public:

		/**
		 * @brief Get mouse button related to the event.
		 * @return The mouse button.
		*/
		MouseButton getMouseButton() const { return _mouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		/**
		 * @brief Only derived classes can instance MouseButtonEvents.
		*/
		MouseButtonEvent(MouseButton button) : _mouseButton(button) {}

		MouseButton _mouseButton;
	};

}
