#include "Font.h"

#include <filesystem>

using namespace Honey;

Font::Font(const std::string& path)
{
	// Open file
	std::ifstream file;
	file.open(path, std::ifstream::binary);

	// Get size in bytes
	std::size_t bytes = file.tellg();
	file.seekg(0, std::ios::end);
	bytes = (std::size_t)file.tellg() - bytes;
	file.seekg(0, std::ios::beg);

	// Read file
	_ttf_buffer = new unsigned char[bytes];
	file.read((char*)_ttf_buffer, bytes);

	file.close(); // Close file
	
	// Init Font
	int offset = stbtt_GetFontOffsetForIndex(_ttf_buffer, 0);
	int success = stbtt_InitFont(&_info, _ttf_buffer, offset);
	HNY_CORE_ASSERT(success, "Failed to Load font!");
}

Font::~Font()
{
	delete[] _ttf_buffer;
}

Reference<Font> Font::CreateFromFile(const std::string& path)
{
	return CreateReference<Font>(path);
}
