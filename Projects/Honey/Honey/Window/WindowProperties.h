#pragma once

#include <string>

#include <Honey/Core.h>

namespace Honey {

	struct HONEY_API WindowProperties {

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Honey Engine - Window", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

}