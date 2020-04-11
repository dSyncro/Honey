#pragma once

#include <Honey/Core.h>

#include <string>

namespace Honey {

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

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class HONEY_API Event {

	public:

		Event() {}
		virtual ~Event() {}

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(int category)
		{
			return GetCategoryFlags() & category;
		}

		bool HasBeenHandled = false;
	};

}

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


inline std::ostream& operator <<(std::ostream& stream, const Honey::Event& e)
{
	return stream << e.ToString();
}