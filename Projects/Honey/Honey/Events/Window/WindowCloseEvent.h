#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API WindowCloseEvent : public Event {

	public:

		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}