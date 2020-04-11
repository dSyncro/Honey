#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API AppUpdateEvent : public Event {

	public:

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}