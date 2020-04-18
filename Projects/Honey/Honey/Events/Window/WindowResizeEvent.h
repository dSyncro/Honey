#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API WindowResizeEvent : public Event {

	public:

		WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {}

		inline unsigned int GetWidth() const { return _width; }
		inline unsigned int GetHeight() const { return _height; }

		virtual std::string ToString() const override
		{
			std::stringstream stream;
			stream << "WindowResizeEvent: " << _width << ", " << _height;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		unsigned int _width, _height;
	};

}