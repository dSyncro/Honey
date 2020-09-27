#pragma once

#include <Honey/Events/Event.h>

namespace Honey {

	/**
	 * @brief Window Close Event.
	 * Usually occurs when a window close message is received.
	*/
	class WindowCloseEvent final : public Event {

	public:

		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
