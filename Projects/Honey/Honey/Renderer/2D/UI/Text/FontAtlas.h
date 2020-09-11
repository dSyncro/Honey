#pragma once

#include "Font.h"
#include "Glyph.h"

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

		std::size_t GetFontHeight() const { return _fontHeight; }
		void SetFontHeight(std::size_t height) { _fontHeight = height; _isDirty = true; }

		void SetCharset(const Math::Span& range) { _charset = range; _isDirty = true; }
		Math::Span GetCharset() const { return _charset; }

		const Glyph& GetGlyph(char c) { return _glyphs[c - _charset.Start]; }
		const Glyph& GetGlyph(std::size_t index) { return _glyphs[index]; }
		
		const Glyph& GetUpdatedGlyph(char c) { Rebuild(); return GetGlyph(c); }
		const Glyph& GetUpdatedGlyph(std::size_t index) { Rebuild(); return GetGlyph(index); }

		std::size_t GetGlyphCount() { return _charset.Length; }

		float GetScaleFactor() const { return _scaleFactor; }
		float GetScaledAscent() const { return _font->_ascent * _scaleFactor; }
		float GetScaledDescent() const { return _font->_descent * _scaleFactor; }

		const Reference<Texture2D>& GetTexture() const { return _texture; }
		const Reference<Font>& GetFont() const { return _font; }

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
		float _scaleFactor;
		Math::Span _charset;

		Glyph* _glyphs = nullptr;

		Reference<Texture2D> _texture = nullptr;
		Reference<Image> _bitmap = nullptr;

		bool _isDirty = true;

		friend class EditorLayer;
	};

}
