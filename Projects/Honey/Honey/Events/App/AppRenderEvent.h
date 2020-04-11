#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	class HONEY_API AppRenderEvent : public Event {

	public:

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}