#pragma once

#include "Font.h"
#include "Glyph.h"

#include <stb_image_write.h>

#include <Honey/Core/Assertion.h>
#include <Honey/Renderer/Texture.h>
#include <Honey/Renderer/Image.h>
#include <Honey/Math/Math.h>

namespace Honey {
	
	class FontAtlas {

	public:

		FontAtlas(const Reference<Font>& font, std::size_t fontHeight, const Math::Span& charset);
		~FontAtlas();

		static Reference<FontAtlas> Create(const Reference<Font>& font, std::size_t fontHeight = 12, const Math::Span& charset = Math::Span(32, 96));

		void Rebuild();

		void WriteToFile(const std::string& filename)
		{
			stbi_write_png(filename.c_str(), (int)_bitmapSize.Width, (int)_bitmapSize.Height, 1, _bitmap->GetRawBitmap(), (int)_bitmapSize.Width);
		}

		void SetFontHeight(std::size_t height) { _fontHeight = height; _isDirty = true; }

		void SetCharset(const Math::Span& range) { _charset = range; _isDirty = true; }
		Math::Span GetCharset() const { return _charset; }

		const Glyph& GetGlyph(char c) { return _glyphs[c - _charset.Start]; }
		const Glyph& GetGlyph(std::size_t index) { return _glyphs[index]; }
		
		const Glyph& GetUpdatedGlyph(char c) { Rebuild(); return GetGlyph(c); }
		const Glyph& GetUpdatedGlyph(std::size_t index) { Rebuild(); return GetGlyph(index); }

		std::size_t GetGlyphCount() { return _charset.Length; }

		const Reference<Texture2D>& GetTexture() const { return _texture; }

		bool IsValid() const { return _font != nullptr; }

		/*
		 * @brief Atlas can become dirty if: \n
		 * - Font changes \n
		 * - Charset changes \n
		 */
		bool IsDirty() const { return _isDirty; }

	private:

		void Free();

		Reference<Font> _font;
		std::size_t _fontHeight;

		Math::Size _bitmapSize = Math::Size(512, 512);
		Math::Span _charset;

		int _ascent = 0;
		int _descent = 0;
		int _lineGap = 0;

		Glyph* _glyphs = nullptr;

		Reference<Texture2D> _texture = nullptr;
		Reference<Image> _bitmap = nullptr;

		bool _isDirty = true;

		friend class EditorLayer;
	};

}
