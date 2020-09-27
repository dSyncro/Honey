#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief App Render Event.
	 * Usually occurs when application renders something.
	*/
	class AppRenderEvent final : public Event {

	public:

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}
