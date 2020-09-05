#pragma once

#include <string>
#include <fstream>

#include <Honey/Core/Assertion.h>
#include <Honey/Core/MemoryManagement.h>
#include <stb_truetype.h>

namespace Honey {

	class Font {
	
	public:

		Font(const std::string& path, std::size_t height);
		~Font();

		static Reference<Font> CreateFromFile(const std::string& path, std::size_t height = 12);

	private:

		stbtt_fontinfo _info;
		std::size_t _height;
		unsigned char* _ttf_buffer;

		friend class FontAtlas;
	};

}
