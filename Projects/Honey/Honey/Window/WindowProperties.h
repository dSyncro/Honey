#pragma once

#include <string>

#include <Honey/Core/TypeTraits.h>

namespace Honey {

	/**
	 * @brief Window properties.
	*/
	struct WindowProperties {

		/** @brief Window title. */
		std::string Title;

		UInt Width; /** @brief Window width. */
		UInt Height; /** @brief Window height. */

		/**
		 * @brief Construct WindowProperties.
		 * @param title Window title.
		 * @param width Window width.
		 * @param height Window height.
		*/
		WindowProperties(const std::string& title = "Honey Engine - Window", UInt width = 1280, UInt height = 720)
			: Title(title), Width(width), Height(height) { }
	};

}
