#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	class WindowResizeEvent final : public Event {

	public:

		WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {}

		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }

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