#include "FontAtlas.h"

using namespace Honey;
using namespace Honey::Math;

FontAtlas::FontAtlas(const Reference<Font>& font, const Math::Span& charset)
	: _font(font), _charset(charset)
{
	Rebuild();
}

void FontAtlas::Rebuild()
{
	// No need to rebuild
	if (!IsDirty || !IsValid()) return;

	Free();

	_glyphs = new AtlasGlyph[_charset.Length];

	// New buffer for baked chars
	stbtt_bakedchar* bakedChars = new stbtt_bakedchar[_charset.Length];

	Reference<Image> bitmap = Image::Create(_bitmapSize.Width, _bitmapSize.Height, 1);
	_bitmap = bitmap;

	stbtt_BakeFontBitmap(
		_font->_info.data,
		0, _font->_height,
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
	float scale = stbtt_ScaleForPixelHeight(&_font->_info, _font->_height);
	int ascent, descent;
	stbtt_GetFontVMetrics(&_font->_info, &ascent, &descent, &_lineGap);
	_ascent = (int)(ascent * scale);
	_descent = (int)(descent * scale);

	// Generate glyphs
	for (int i = _charset.Start; i < _charset.GetEnd(); i++)
	{
		AtlasGlyph& g = _glyphs[i - _charset.Start];
		g.Atlas = this;
		char c = g.Character = (char)i;
		float x, y; stbtt_aligned_quad alignedQuad;
		stbtt_GetBakedQuad(bakedChars, _bitmapSize.Width, _bitmapSize.Height, c - _charset.Start, &x, &y, &alignedQuad, true);
		g.Face = Rect::FromBounds(Point(alignedQuad.x0, alignedQuad.y0), Point(alignedQuad.x1, alignedQuad.y1));
		g.UV = Rect::FromBounds(Point(alignedQuad.s0, alignedQuad.t0), Point(alignedQuad.s1, alignedQuad.t1));
	}

	delete[] bakedChars;
}

void FontAtlas::Free()
{
	if (_glyphs) delete[] _glyphs;
	_glyphs = nullptr;
}
