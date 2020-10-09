#pragma once

#include <sstream>

#include <Honey/Events/Event.h>
#include <Honey/Math/Size.h>

namespace Honey {

	/**
	 * @brief Window Resize Event.
	 * Usually occurs when a window resize message is received.
	*/
	class WindowResizeEvent final : public Event {

	public:

		/**
		 * @brief Construct WindowResizeEvent from Size.
		 * @param size New size.
		*/
		WindowResizeEvent(const Math::Size& size) : _size(size) {}

		/**
		 * @brief Construct WindowResizeEvent from width and height.
		 * @param width New width.
		 * @param height New height.
		*/
		WindowResizeEvent(UInt width, UInt height) : _size(width, height) {}

		/**
		 * @brief Get new Window size.
		 * @return Window size.
		*/
		const Math::Size& getSize() const { return _size; }

		/**
		 * @see Event::toString()
		*/
		virtual std::string toString() const override
		{
			std::stringstream stream;
			stream << "WindowResizeEvent: " << _size.width << ", " << _size.height;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		Math::Size _size;
	};

}
