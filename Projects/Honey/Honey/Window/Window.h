#pragma once

#include <functional>

#include <Honey/Events/Event.h>

#include "WindowProperties.h"

namespace Honey {

	class HONEY_API Window {

	public:

		using WindowEventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const WindowEventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());

	};

}