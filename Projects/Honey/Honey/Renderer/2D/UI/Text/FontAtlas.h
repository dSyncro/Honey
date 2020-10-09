#pragma once

#include "Font.h"
#include "Glyph.h"

#include <Honey/Core/Assertion.h>
#include <Honey/Renderer/Texture.h>
#include <Honey/Renderer/Image.h>
#include <Honey/Math/Math.h>

namespace Honey {
	
	/**
	 * @brief Font Atlas API
	*/
	class FontAtlas {

	public:

		/**
		 * @brief Construct FontAtlas.
		 * @param font The font used by the atlas.
		 * @param fontHeight The font height.
		 * @param charset The font atlas charset.
		*/
		FontAtlas(const Reference<Font>& font, UInt fontHeight, const Math::Span& charset);
		~FontAtlas();

		/**
		 * @brief Create a new font atlas.
		 * @param font The font used by the atlas. 
		 * @param fontHeight The font height.
		 * @param charset The font atlas charset.
		 * @return A new memory managed font atlas.
		*/
		static Reference<FontAtlas> create(const Reference<Font>& font, UInt fontHeight = 12, const Math::Span& charset = Math::Span(32, 96));

		/**
		 * @brief Rebuild font Atlas.
		 * Operation is performed only if needed
		 * (that is when Atlas is dirty and valid).
		*/
		void rebuild();

		/**
		 * @brief Get font height.
		 * @return The font height.
		*/
		UInt fontHeight() const { return _fontHeight; }

		/**
		 * @brief Set font height.
		 * @param height New height.
		*/
		void fontHeight(UInt height) { _fontHeight = height; _isDirty = true; }

		/**
		 * @brief Get charset.
		 * @return Get Font Atlas charset.
		*/
		Math::Span charset() const { return _charset; }

		/**
		 * @brief Set new charset.
		 * @param range The new charset range.
		*/
		void charset(const Math::Span& range) { _charset = range; _isDirty = true; }

		/**
		 * @brief Get glyph from char.
		 * @param c The char.
		 * @return Glyph associated with c.
		*/
		const Glyph& getGlyph(char c) { return _glyphs[c - _charset.start]; }

		/**
		 * @brief Get glyph from index.
		 * @param index The index.
		 * @return Glyph associated with index.
		*/
		const Glyph& getGlyph(UInt index) { return _glyphs[index]; }
		
		/**
		 * @brief Get glyph from char having care to update atlas if it is dirty.
		 * @param c The char.
		 * @return Glyph associated with c.
		*/
		const Glyph& getUpdatedGlyph(char c) { rebuild(); return getGlyph(c); }

		/**
		 * @brief Get glyph from index having care to update atlas if it is dirty.
		 * @param c The index.
		 * @return Glyph associated with index.
		*/
		const Glyph& getUpdatedGlyph(UInt index) { rebuild(); return getGlyph(index); }

		/**
		 * @brief Get glyph count.
		 * @return The glyph count.
		*/
		UInt getGlyphCount() { return _charset.length; }

		/**
		 * @brief Get font scale factor to height.
		 * @return Scale factor.
		*/
		Float getScaleFactor() const { return _scaleFactor; }

		/**
		 * @brief Get font ascent scaled to height.
		 * @return Scaled ascent.
		*/
		Float getScaledAscent() const { return _font->_ascent * _scaleFactor; }

		/**
		 * @brief Get font descent scaled to height.
		 * @return Scaled descent.
		*/
		Float getScaledDescent() const { return _font->_descent * _scaleFactor; }

		/**
		 * @brief Get atlas underlying texture.
		 * @return Atlas texture.
		*/
		const Reference<Texture2D>& getTexture() const { return _texture; }

		/**
		 * @brief Get atlas font.
		 * @return The font.
		*/
		const Reference<Font>& getFont() const { return _font; }

		/**
		 * @brief Check if this is a valid font atlas.
		*/
		bool isValid() const { return _font != nullptr; }

		/*
		 * @brief Atlas can become dirty if:
		 * Font changes,
		 * charset changes.
		 * Being dirty mean that concrete changes have been made
		 * to the atlas and therefore it needs to be updated.
		 */
		bool isDirty() const { return _isDirty; }

	private:

		void free();

		Reference<Font> _font;
		UInt _fontHeight;
		Float _scaleFactor;
		Math::Span _charset;

		Glyph* _glyphs = nullptr;

		Reference<Texture2D> _texture = nullptr;
		Reference<Image> _bitmap = nullptr;

		bool _isDirty = true;

		friend class EditorLayer;
	};

}
