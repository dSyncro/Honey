#include "FontAtlas.h"

using namespace Honey;
using namespace Honey::Math;

FontAtlas::FontAtlas(const Reference<Font>& font, UInt fontHeight, const Span& charset)
	: _font(font), _fontHeight(fontHeight), _charset(charset)
{
	rebuild();
}

FontAtlas::~FontAtlas()
{
	free();
}

Reference<FontAtlas> FontAtlas::create(const Reference<Font>& font, UInt fontHeight, const Span& charset)
{
	return CreateReference<FontAtlas>(font, fontHeight, charset);
}

void FontAtlas::rebuild()
{
	// No need to rebuild
	if (!isDirty() || !isValid()) return;

	// Free old resources
	free();

	// Allocate glyphs
	_glyphs = new Glyph[_charset.length];

	// New buffer for baked chars
	stbtt_bakedchar* bakedChars = new stbtt_bakedchar[_charset.length];

	// Bake font to bitmap
	Reference<Image> bitmap = Image::create(512, 512, 1);
	_bitmap = bitmap;

	stbtt_BakeFontBitmap(
		_font->_info.data,
		0, static_cast<float>(_fontHeight),
		(unsigned char*)bitmap->getRawBitmap(),
		bitmap->getWidth(), bitmap->getHeight(),
		_charset.start, _charset.length,
		bakedChars
	);

	// Create texture
	_texture = Texture2D::create(bitmap->getWidth(), bitmap->getHeight(), Texture2D::PixelFormat::R);
	_texture->setData(bitmap->getRawBitmap(), bitmap->getSizeInBytes());

	// Write to file
	 _bitmap->writeToPNG("Test.png");

	// Get font metrics
	_scaleFactor = stbtt_ScaleForPixelHeight(&_font->_info, static_cast<float>(_fontHeight));

	// Generate glyphs
	for (UInt i = _charset.start; i < _charset.end(); i++)
	{
		UInt realIndex = i - _charset.start;
		const stbtt_bakedchar* bc = bakedChars + realIndex;
		Glyph& g = _glyphs[realIndex];

		char c = g.character = static_cast<char>(i);
		float ipw = 1.0f / static_cast<float>(_texture->getWidth());
		float iph = 1.0f / static_cast<float>(_texture->getHeight());

		g.offset = Vector2(bc->xoff, bc->yoff);
		g.boundingBox = Rect::fromBounds(Point(bc->x0, bc->y0), Point(bc->x1, bc->y1));

		// Calculate glyph UV
		float uv_x0, uv_y0, uv_x1, uv_y1;
		uv_x0 = bc->x0 * ipw;
		uv_y0 = bc->y0 * iph;
		uv_x1 = bc->x1 * ipw;
		uv_y1 = bc->y1 * iph;

		g.uv = {
			Vector2(uv_x0, uv_y0),
			Vector2(uv_x1, uv_y0),
			Vector2(uv_x1, uv_y1),
			Vector2(uv_x0, uv_y1),
		};

		g.advance = bc->xadvance;
	}

	delete[] bakedChars;
}

void FontAtlas::free()
{
	if (_glyphs) delete[] _glyphs;
	_glyphs = nullptr;
}
