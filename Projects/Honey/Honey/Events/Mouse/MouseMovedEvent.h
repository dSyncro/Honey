#pragma once

#include <sstream>

#include <Honey/Events/Event.h>
#include <Honey/Math/Vector/Vector2.h>

namespace Honey {

	/**
	 * @brief Mouse Moved Event.
	 * Usually occurs when the cursor moves from its previous position.
	*/
	class MouseMovedEvent final : public Event {

	public:

		MouseMovedEvent(const Math::Vector2& position) : _position(position) { }
		MouseMovedEvent(float x, float y) : _position(x, y) { }

		/**
		 * @brief New x-coordinate.
		 * @return x-coordinate.
		*/
		float x() const { return _position.x; }

		/**
		 * @brief New y-coordinate.
		 * @return y-coordinate.
		*/
		float y() const { return _position.y; }

		const Math::Vector2& getPosition() const { return _position; }

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

		Math::Vector2 _position;
	};

}
