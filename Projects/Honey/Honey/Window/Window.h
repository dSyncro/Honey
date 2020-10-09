#pragma once

#include <functional>

#include <Honey/Events/Event.h>
#include <Honey/Math/Size.h>

#include "WindowProperties.h"

namespace Honey {

	/**
	 * @brief Abstract Window class.
	*/
	class Window {

	public:

		/**
		 * @brief Window Event Callback function type.
		*/
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() = default;

		/**
		 * @brief Called when window gets updated.
		*/
		virtual void onUpdate() = 0;

		/**
		 * @brief Get window width.
		 * @return The width.
		*/
		virtual UInt getWidth() const = 0;

		/**
		 * @brief Get window height.
		 * @return The height.
		*/
		virtual UInt getHeight() const = 0;

		/**
		 * @brief Get window size.
		 * @return The size.
		*/
		virtual Math::Size getSize() const = 0;

		/**
		 * @brief Set a new title to window.
		 * @param title New title.
		*/
		virtual void setTitle(const std::string& title) = 0;

		/**
		 * @brief Set new event callback for window.
		 * @param callback New event callback.
		*/
		virtual void setEventCallback(const EventCallback& callback) = 0;

		/**
		 * @brief Set if VSync is enabled or not for window.
		 * @param enabled Is VSync enabled?
		*/
		virtual void setVSync(bool enabled) = 0;

		/**
		 * @brief Check if VSync is enabled for window.
		*/
		virtual bool isVSyncEnabled() const = 0;

		/**
		 * @brief Get underlying window.
		 * @return Native window.
		*/
		virtual void* getNativeWindow() const = 0;

		/**
		 * @brief Create a window.
		 * @param properties Window properties.
		 * @return A new unique window.
		*/
		static Unique<Window> create(const WindowProperties& properties = WindowProperties());

	};

}
