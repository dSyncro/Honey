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

		/**
		 * @brief Construct MouseScrolledEvent from offset.
		 * @param offset Scroll offset.
		*/
		MouseScrolledEvent(const Math::Vector2& offset) : _offset(offset) {}

		/**
		 * @brief Construct MouseScrolledEvent from offset components.
		 * @param xOffset Offset X component.
		 * @param yOffset Offset Y component.
		*/
		MouseScrolledEvent(Float xOffset, Float yOffset) : _offset(xOffset, yOffset) {}

		/**
		 * @brief Get horizontal scroll offset.
		 * @return X scroll offset.
		*/
		Float getXOffset() const { return _offset.x; }

		/**
		 * @brief Get vertical scroll offset.
		 * @return Y scroll offset.
		*/
		Float getYOffset() const { return _offset.y; }

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
