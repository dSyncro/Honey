#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API MouseScrolledEvent : public Event {

	public:

		MouseScrolledEvent(float xOffset, float yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

		float GetXOffset() const { return _xOffset; }
		float GetYOffset() const { return _yOffset; }

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseScrolledEvent: " << _xOffset << ", " << _yOffset;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		float _xOffset, _yOffset;
	};

}