#pragma once

#include <sstream>

#include <Honey/Events/Event.h>
#include <Honey/Math/Point.h>

namespace Honey {

	/**
	 * @brief Mouse Moved Event.
	 * Usually occurs when the cursor moves from its previous position.
	*/
	class MouseMovedEvent final : public Event {

	public:

		/**
		 * @brief Construct MouseMovedEvent from position.
		 * @param position The position.
		*/
		MouseMovedEvent(const Math::Point& position) : _position(position) { }

		/**
		 * @brief Construct MouseMovedEvent from coordinates.
		 * @param x X coordinate.
		 * @param y Y coordinate.
		*/
		MouseMovedEvent(Int x, Int y) : _position(x, y) { }

		/**
		 * @brief New x-coordinate.
		 * @return x-coordinate.
		*/
		Int x() const { return _position.x; }

		/**
		 * @brief New y-coordinate.
		 * @return y-coordinate.
		*/
		Int y() const { return _position.y; }

		const Math::Point& getPosition() const { return _position; }

		/**
		 * @see Event::toString() 
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "MouseMovedEvent: " << _position.x << ", " << _position.y;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		Math::Point _position;
	};

}
