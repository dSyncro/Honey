#pragma once

#include <string>
#include <fstream>

#include <Honey/Core/Assertion.h>
#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Rect.h>
#include <stb_truetype.h>

namespace Honey {

	/**
	 * @brief Font API
	*/
	class Font {
	
	public:

		/**
		 * @brief Construct a new font.
		 * @param path Font file path.
		*/
		Font(const std::string& path);
		~Font();

		/**
		 * @brief Create font from file.
		 * @param path The file path.
		 * @return A new memory managed Font from path.
		*/
		static Reference<Font> createFromFile(const std::string& path);

		/**
		 * @brief Get font ascent.
		 * @return Font ascent.
		*/
		Int getAscent() const { return _ascent; }

		/**
		 * @brief Get font descent.
		 * @return Font descent.
		*/
		Int getDescent() const { return _descent; }

		/**
		 * @brief Get font line gap.
		 * @return Font line gap.
		*/
		Int getLineGap() const { return _lineGap; }

		/**
		 * @brief Get kerning between two characters.
		 * @param a First character.
		 * @param b Second character.
		 * @return Kerning between a and b.
		*/
		Int getKerning(const char a, const char b);

	private:

		stbtt_fontinfo _info;
		unsigned char* _ttf_buffer;

		Int _ascent = 0, _descent = 0, _lineGap = 0;

		friend class FontAtlas;
	};

}
