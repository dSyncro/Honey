#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API MouseMovedEvent : public Event {

	public:

		MouseMovedEvent(float x, float y) : _x(x), _y(y) { }

		inline float GetX() const { return _x; }
		inline float GetY() const { return _y; }

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