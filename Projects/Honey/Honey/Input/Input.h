#pragma once

#include "Keycode.h"
#include "MouseButtons.h"
#include "KeyMods.h"
#include "KeyState.h"

#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Vector/Vector2.h>

namespace Honey {

	/**
	 * @brief Input API
	*/
	class Input {

	public:

		// Pure static class

		Input() = delete;
		Input(const Input&) = delete;
		Input& operator =(const Input&) = delete;

		/**
		 * @brief Check if key is pressed.
		 * @param keycode The key.
		*/
		static bool isKeyPressed(Keycode keycode);

		/**
		 * @brief Check if mouse button is pressed.
		 * @param button The mouse button.
		*/
		static bool isMousePressed(MouseButton button);

		/**
		 * @brief Get mouse X position.
		 * @return Mouse X position.
		*/
		static float getMouseX();

		/**
		 * @brief Get mouse Y position.
		 * @return Mouse Y position.
		*/
		static float getMouseY();

		/**
		 * @brief Get mouse position.
		 * @return Mouse position.
		*/
		static Math::Vector2 getMousePosition();

		/**
		 * @brief Get mouse vertical scroll.
		 * @return Mouse vertical scroll since last frame.
		*/
		static float getVMouseScroll();

		/**
		 * @brief Get mouse horizontal scroll.
		 * @return Mouse horizontal scroll since last frame.
		*/
		static float getHMouseScroll();

		/**
		 * @brief Get key mods.
		 * Common key mods are [CTRL], [ALT], [SUPER].
		 * @return Get key mods.
		*/
		static uint16_t getKeyMods();

		/**
		 * @brief Get state of a certain key.
		 * @param keycode The key.
		 * @return State of the key.
		*/
		static KeyState getKeyState(Keycode keycode);

		/**
		 * @brief Get state of a certain mouse button.
		 * @param button The mouse button.
		 * @return State of the button.
		*/
		static KeyState getMouseButtonState(MouseButton button);

	private:

		// TODO: Improve Input Polling situation

		static Math::Vector2& mouseScrollAmount() { static Math::Vector2 scroll; return scroll; }

		friend class GlfwPlatformsWindow;
	};

}
