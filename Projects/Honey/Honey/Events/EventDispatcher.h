#pragma once

#include <functional>

#include "Event.h"

namespace Honey {

	class EventDispatcher {

		template <typename T>
		using EventCallback = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& e) : _event(e) {}

		template <typename T>
		bool Dispatch(EventCallback<T> callback)
		{
			if (_event.GetEventType() != T::GetStaticType()) return false;

			_event.HasBeenHandled = callback(static_cast<T&>(_event));
			return true;
		}

	private:

		Event& _event;
	};

}