#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief App Tick Event
	 * Usually occurs after an Application Tick.
	*/
	class AppTickEvent final : public Event {

	public:

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}
