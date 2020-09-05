#pragma once

#include "Font.h"

#include <stb_image_write.h>

#include <Honey/Core/Assertion.h>
#include <Honey/Renderer/Texture.h>
#include <Honey/Renderer/Image.h>
#include <Honey/Math/Math.h>

namespace Honey {

	class FontAtlas;

	struct AtlasGlyph {

		AtlasGlyph(FontAtlas* atlas = nullptr, 
			const char character = 0, 
			const Math::Rect& face = Math::Rect(0, 0, 0, 0),
			const Math::Rect& uv = Math::Rect(0, 0, 0, 0))
			: Atlas(atlas), Character(character), Face(face), UV(uv) { }

		FontAtlas* Atlas;

		char Character;
		Math::Rect Face;
		Math::Rect UV;

	};

	class FontAtlas {

	public:

		FontAtlas(const Reference<Font>& font, const Math::Span& charset);

		static Reference<FontAtlas> Create(const Reference<Font>& font, const Math::Span& charset = Math::Span(32, 96))
		{
			return CreateReference<FontAtlas>(font, charset);
		}

		~FontAtlas()
		{
			Free();
		}

		void Rebuild();

		void WriteToFile(const std::string& filename)
		{
			stbi_write_png(filename.c_str(), (int)_bitmapSize.Width, (int)_bitmapSize.Height, 1, _bitmap->GetRawBitmap(), (int)_bitmapSize.Width);
		}

		void SetCharset(const Math::Span& range) { _charset = range; IsDirty = true; }
		Math::Span GetCharset() const { return _charset; }

		const AtlasGlyph& GetGlyph(char c) { return _glyphs[c - _charset.Start]; }
		const AtlasGlyph& GetGlyph(std::size_t index) { return _glyphs[index]; }

		std::size_t GetGlyphCount() { return _charset.Length; }

		bool IsValid() const { return _font != nullptr; }

		/*
		 * @brief Atlas can become dirty if: \n
		 * - Font changes \n
		 * - Charset changes \n
		 */
		bool IsDirty = true;

	private:

		void Free();

		Reference<Font> _font;

		Math::Size _bitmapSize = Math::Size(512, 512);
		Math::Span _charset;

		int _ascent = 0;
		int _descent = 0;
		int _lineGap = 0;

		AtlasGlyph* _glyphs = nullptr;

		Reference<Texture2D> _texture = nullptr;
		Reference<Image> _bitmap = nullptr;

		friend class EditorLayer;
	};

}
