#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API MouseButtonEvent : public Event {

	public:

		int GetMouseButton() const { return _mouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		MouseButtonEvent(int button) : _mouseButton(button) {}

		int _mouseButton;
	};

}