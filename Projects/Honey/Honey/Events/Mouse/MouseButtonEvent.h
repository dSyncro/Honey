#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

#include <Honey/Input/MouseButtons.h>

namespace Honey {

	class HONEY_API MouseButtonEvent : public Event {

	public:

		MouseButton GetMouseButton() const { return _mouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		MouseButtonEvent(MouseButton button) : _mouseButton(button) {}

		MouseButton _mouseButton;
	};

}