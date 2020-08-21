#pragma once

#include <functional>

#include <Honey/Events/Event.h>
#include <Honey/Math/Vector/Vector2.h>

#include "WindowProperties.h"

namespace Honey {

	class Window {

	public:

		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual Math::Vector2 GetSize() const = 0;

		virtual void SetTitle(const std::string& title) = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Unique<Window> Create(const WindowProperties& properties = WindowProperties());

	};

}
