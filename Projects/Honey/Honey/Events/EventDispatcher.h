#pragma once

#include <functional>

#include "Event.h"

namespace Honey {

	class HONEY_API EventDispatcher {

		template <typename T>
		using EventCallback = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& e) : _event(e) {}

		template <typename T>
		bool Dispatch(EventCallback<T> callback)
		{
			if (_event.GetEventType() == T::GetStaticType())
			{
				_event.HasBeenHandled = callback(*(T*)&_event);
				return true;
			}
			return false;
		}

	private:

		Event& _event;
	};

}