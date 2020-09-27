#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief App Update Event.
	 * Usually occurs when Application is updated.
	*/
	class AppUpdateEvent final : public Event {

	public:

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}
