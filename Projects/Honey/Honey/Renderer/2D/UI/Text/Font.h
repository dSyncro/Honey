#pragma once

#include <string>
#include <fstream>

#include <Honey/Core/Assertion.h>
#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Rect.h>
#include <stb_truetype.h>

namespace Honey {

	class Font {
	
	public:

		Font(const std::string& path);
		~Font();

		static Reference<Font> CreateFromFile(const std::string& path);

		int GetAscent() const { return _ascent; }
		int GetDescent() const { return _descent; }
		int GetLineGap() const { return _lineGap; }

		int GetKerning(const char a, const char b);

	private:

		stbtt_fontinfo _info;
		unsigned char* _ttf_buffer;

		int _ascent = 0, _descent = 0, _lineGap = 0;

		friend class FontAtlas;
	};

}
