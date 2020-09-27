#pragma once

#include <sstream>

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief Mouse Scrolled Event.
	 * Usually occurs when either an horizontal
	 * or a vertical mouse scroll is received.
	*/
	class MouseScrolledEvent final : public Event {

	public:

		MouseScrolledEvent(const Math::Vector2& offset) : _offset(offset) {}
		MouseScrolledEvent(float xOffset, float yOffset) : _offset(xOffset, yOffset) {}

		/**
		 * @brief Get horizontal scroll offset.
		 * @return X scroll offset.
		*/
		float getXOffset() const { return _offset.x; }

		/**
		 * @brief Get vertical scroll offset.
		 * @return Y scroll offset.
		*/
		float getYOffset() const { return _offset.y; }

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "MouseScrolledEvent: " << _offset.x << ", " << _offset.y;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		Math::Vector2 _offset;
	};

}
