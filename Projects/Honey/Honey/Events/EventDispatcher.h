#pragma once

#include <functional>

#include "Event.h"

namespace Honey {

	/**
	 * @brief Used to dispatch event to a proper listener function.
	*/
	class EventDispatcher {

	public:

		/**
		 * @brief EventDispatcher Callback function type.
		 * @tparam T Event type.
		*/
		template <typename T>
		using CallbackType = std::function<bool(T&)>;

		/**
		 * @brief Build a dispatcher on top of an event.
		 * @param e The event.
		*/
		EventDispatcher(Event& e) : _event(e) {}

		/**
		 * @brief Dispatch to function if it is of the specified type.
		 * @tparam T Type required to dispatch.
		 * @param callback Callback function.
		 * @return A boolean expressing if the event got dispatched.
		*/
		template <typename T>
		bool Dispatch(CallbackType<T> callback)
		{
			if (_event.getEventType() != T::getStaticType()) return false;

			_event.hasBeenHandled = callback(static_cast<T&>(_event));
			return true;
		}

	private:

		Event& _event;
	};

}
