#if 0

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "FontLibrary.h"

using namespace Honey;

FontLibrary::FontLibrary()
{
	int result = FT_Init_FreeType(&_library);
	HNY_CORE_ASSERT(result == 0, "Failed to initialize Font Library!");
}

FontLibrary::~FontLibrary()
{
	int result = FT_Done_FreeType(_library);
	HNY_CORE_ASSERT(result == 0, "Failed to dispose Font Library!");
}

void FontLibrary::AddFont(const Reference<Font>& font)
{
	FT_Face face;
	int result = FT_New_Face(_library, font->Filename.c_str(), 0, &face);
	HNY_CORE_ASSERT(result == 0, "Failed to load Font!");

	font->_face = face;
}

void FontLibrary::RemoveFont(const Reference<Font>& font)
{
	int result = FT_Done_Face(font->_face);
	HNY_CORE_ASSERT(result == 0, "Failed to dispose Font!");

	font->_face = nullptr;
}

#endif
