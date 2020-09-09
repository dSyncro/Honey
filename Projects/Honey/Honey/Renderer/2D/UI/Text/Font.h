#pragma once

#include <string>
#include <fstream>

#include <Honey/Core/Assertion.h>
#include <Honey/Core/MemoryManagement.h>
#include <stb_truetype.h>

namespace Honey {

	class Font {
	
	public:

		Font(const std::string& path);
		~Font();

		static Reference<Font> CreateFromFile(const std::string& path);

	private:

		stbtt_fontinfo _info;
		unsigned char* _ttf_buffer;

		friend class FontAtlas;
	};

}
