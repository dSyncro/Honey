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

	Reference<Image> bitmap = Image::Create(512, 512, 1);
	_bitmap = bitmap;

	stbtt_BakeFontBitmap(
		_font->_info.data,
		0, _fontHeight,
		(unsigned char*)bitmap->GetRawBitmap(),
		bitmap->GetWidth(), bitmap->GetHeight(),
		_charset.Start, _charset.Length,
		bakedChars
	);

	_texture = Texture2D::Create(bitmap->GetWidth(), bitmap->GetHeight(), Texture2D::PixelFormat::R);
	_texture->SetData(bitmap->GetRawBitmap(), bitmap->GetSizeInBytes());

	// Write to file
	 _bitmap->WriteToPNG("Test.png");

	// Get font metrics
	_scaleFactor = stbtt_ScaleForPixelHeight(&_font->_info, _fontHeight);

	// Generate glyphs
	for (std::size_t i = _charset.Start; i < _charset.GetEnd(); i++)
	{
		std::size_t realIndex = i - _charset.Start;
		const stbtt_bakedchar* bc = bakedChars + realIndex;
		Glyph& g = _glyphs[realIndex];

		g.Bearing = Vector2(bc->xoff, bc->yoff);

		char c = g.Character = (char)i;
		float ipw = 1.0f / (float)_texture->GetWidth();
		float iph = 1.0f / (float)_texture->GetHeight();

		g.BoundingBox = Math::Rect::FromBounds(Point(bc->x0, bc->y0), Point(bc->x1, bc->y1));

		float uv_x0, uv_y0, uv_x1, uv_y1;
		uv_x0 = bc->x0 * ipw;
		uv_y0 = bc->y0 * iph;
		uv_x1 = bc->x1 * ipw;
		uv_y1 = bc->y1 * iph;

		g.UV = {
			Vector2(uv_x0, uv_y0),
			Vector2(uv_x1, uv_y0),
			Vector2(uv_x1, uv_y1),
			Vector2(uv_x0, uv_y1),
		};

		g.Advance = bc->xadvance;

		int x0, y0, x1, y1;
		stbtt_GetGlyphBitmapBox(&_font->_info, i, _scaleFactor, _scaleFactor, &x0, &y0, &x1, &y1);
		g.ClassicBearing.Y = x0;

		int lb, adv;
		stbtt_GetGlyphHMetrics(&_font->_info, i, &adv, &lb);
		g.ClassicBearing.X = lb * _scaleFactor;

		g.ClassicAdv = adv * _scaleFactor;
	}

	delete[] bakedChars;
}

void FontAtlas::Free()
{
	if (_glyphs) delete[] _glyphs;
	_glyphs = nullptr;
}
