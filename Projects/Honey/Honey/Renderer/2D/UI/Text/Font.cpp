#include "Font.h"

#include <filesystem>

using namespace Honey;

Font::Font(const std::string& path)
{
	// Open file
	std::ifstream file;
	file.open(path, std::ifstream::binary);

	// Get size in bytes
	ULong bytes = file.tellg();
	file.seekg(0, std::ios::end);
	bytes = static_cast<ULong>(file.tellg()) - bytes;
	file.seekg(0, std::ios::beg);

	// Read file
	_ttf_buffer = new unsigned char[bytes];
	file.read((char*)_ttf_buffer, bytes);

	file.close(); // Close file
	
	// Init Font
	Int offset = stbtt_GetFontOffsetForIndex(_ttf_buffer, 0);
	Int success = stbtt_InitFont(&_info, _ttf_buffer, offset);
	HNY_CORE_ASSERT(success, "Failed to Load font!");

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&_info, &ascent, &descent, &lineGap);

	_ascent = static_cast<Int>(ascent);
	_descent = static_cast<Int>(descent);
	_lineGap = static_cast<Int>(lineGap);
}

Font::~Font()
{
	delete[] _ttf_buffer;
}

Reference<Font> Font::createFromFile(const std::string& path)
{
	return CreateReference<Font>(path);
}

Int Font::getKerning(const char a, const char b)
{
	return static_cast<Int>(stbtt_GetGlyphKernAdvance(&_info, a, b));
}
