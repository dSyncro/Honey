#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class WindowCloseEvent final : public Event {

	public:

		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}