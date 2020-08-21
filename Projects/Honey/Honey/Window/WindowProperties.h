#pragma once

#include <string>

namespace Honey {

	struct WindowProperties {

		std::string Title;

		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = std::string("Honey Engine - Window"), uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) { }
	};

}
