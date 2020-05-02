#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class MouseMovedEvent final : public Event {

	public:

		MouseMovedEvent(float x, float y) : _x(x), _y(y) { }

		float GetX() const { return _x; }
		float GetY() const { return _y; }

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseMovedEvent: " << _x << ", " << _y;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		float _x, _y;
	};

}