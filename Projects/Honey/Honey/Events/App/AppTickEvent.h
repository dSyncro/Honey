#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API AppTickEvent : public Event {

	public:

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}