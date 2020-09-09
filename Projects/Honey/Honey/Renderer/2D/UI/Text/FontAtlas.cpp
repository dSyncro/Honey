#include "FontAtlas.h"

using namespace Honey;
using namespace Honey::Math;

FontAtlas::FontAtlas(const Reference<Font>& font, std::size_t fontHeight, const Span& charset)
	: _font(font), _fontHeight(fontHeight), _charset(charset)
{
	Rebuild();
}

FontAtlas::~FontAtlas()
{
	Free();
}

Reference<FontAtlas> FontAtlas::Create(const Reference<Font>& font, std::size_t fontHeight, const Span& charset)
{
	return CreateReference<FontAtlas>(font, fontHeight, charset);
}

void FontAtlas::Rebuild()
{
	// No need to rebuild
	if (!IsDirty() || !IsValid()) return;

	Free();

	_glyphs = new Glyph[_charset.Length];

	// New buffer for baked chars
	stbtt_bakedchar* bakedChars = new stbtt_bakedchar[_charset.Length];

	Reference<Image> bitmap = Image::Create(_bitmapSize.Width, _bitmapSize.Height, 1);
	_bitmap = bitmap;

	stbtt_BakeFontBitmap(
		_font->_info.data,
		0, _fontHeight,
		(unsigned char*)bitmap->GetRawBitmap(),
		_bitmapSize.Width, _bitmapSize.Height,
		_charset.Start, _charset.Length,
		bakedChars
	);

	_texture = Texture2D::Create(_bitmapSize.Width, _bitmapSize.Height, Texture2D::PixelFormat::R);
	_texture->SetData(bitmap->GetRawBitmap(), bitmap->GetSizeInBytes());

	// Write to file
	WriteToFile("test.png");

	// Get font metrics
	float scale = stbtt_ScaleForPixelHeight(&_font->_info, _fontHeight);
	int ascent, descent;
	stbtt_GetFontVMetrics(&_font->_info, &ascent, &descent, &_lineGap);
	_ascent = (int)(ascent * scale);
	_descent = (int)(descent * scale);

	// Generate glyphs
	for (std::size_t i = _charset.Start; i < _charset.GetEnd(); i++)
	{
		std::size_t realIndex = i - _charset.Start;
		const stbtt_bakedchar* bc = bakedChars + realIndex;
		Glyph& g = _glyphs[realIndex];
		g.Bearing = Vector2(bc->xoff, bc->yoff);
		g.Advance = bc->xadvance;
		char c = g.Character = (char)i;
		float x = 0.0f, y = 0.0f; stbtt_aligned_quad alignedQuad;
		stbtt_GetBakedQuad(bakedChars, _bitmapSize.Width, _bitmapSize.Height, c - _charset.Start, &x, &y, &alignedQuad, true);
		g.Face = Rect::FromBounds(Point(alignedQuad.x0, alignedQuad.y0), Point(alignedQuad.x1, alignedQuad.y1));
		g.UV = {
			Vector2(alignedQuad.s0, alignedQuad.t1),
			Vector2(alignedQuad.s1, alignedQuad.t1),
			Vector2(alignedQuad.s1, alignedQuad.t0),
			Vector2(alignedQuad.s0, alignedQuad.t0),
		};
	}

	delete[] bakedChars;
}

void FontAtlas::Free()
{
	if (_glyphs) delete[] _glyphs;
	_glyphs = nullptr;
}
