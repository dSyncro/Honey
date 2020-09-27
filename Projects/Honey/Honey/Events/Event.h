#pragma once

#include <string>
#include <ostream>

#include <Honey/Core.h>

namespace Honey {

	/**
	 * @brief All possible Event types.
	*/
	enum class EventType
	{
		None = 0,

		// Window Events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,

		// App Events
		AppTick, AppUpdate, AppRender,

		// Key Events
		KeyPressed, KeyReleased, KeyTyped,

		// Mouse Events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * @brief All possible Event categories.
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	/**
	 * @brief Base class for events.
	*/
	class Event {

	public:

		Event() = default;
		virtual ~Event() = default;

		/**
		 * @brief Get event type.
		 * @return Event type.
		*/
		virtual EventType getEventType() const = 0;

		/**
		 * @brief Get event name.
		 * @return Event name.
		*/
		virtual const char* getName() const = 0;

		/**
		 * @brief Get the categories this event belongs to
		 * in flag format.
		 * @return Category flag.
		*/
		virtual int getCategoryFlags() const = 0;

		/**
		 * @brief Convert event to string.
		 * @return Event information in a nice formatted string.
		*/
		virtual std::string toString() const { return getName(); }

		/**
		 * @brief Check if event belongs to a particular category.
		 * @param category Category to perform the check with.
		 * @return A boolean expressing if event belongs to category.
		*/
		bool isInCategory(int category) { return getCategoryFlags() & category; }

		/**
		 * @brief Event has already been handled?
		*/
		bool hasBeenHandled = false;
	};
}

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
									virtual EventType getEventType() const override { return getStaticType(); } \
									virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

/**
 * @brief Push event to ostream.
 * @param stream The stream.
 * @param e The event.
 * @return The reference to the stream.
*/
inline std::ostream& operator <<(std::ostream& stream, const Honey::Event& e)
{
	return stream << e.toString();
}
