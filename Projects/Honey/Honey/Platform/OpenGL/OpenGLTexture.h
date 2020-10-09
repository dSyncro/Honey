#pragma once

#include <Honey/Renderer/Texture.h>

namespace Honey {

	/**
	 * @brief OpenGL texture 2D implementation.
	*/
	class OpenGLTexture2D final : public Texture2D {

	public:

		OpenGLTexture2D(UInt width, UInt height, PixelFormat format);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		/**
		 * @brief Get texture width.
		 * @return Texture width.
		*/
		virtual UInt getWidth() const override { return _width; }

		/**
		 * @brief Get texture height.
		 * @return Texture height.
		*/
		virtual UInt getHeight() const override { return _height; }

		/**
		 * @brief Get texture size.
		 * @return Texture size.
		*/
		virtual Math::Size getSize() const override { return Math::Size(_width, _height); }

		/**
		 * @brief Get pointer to raw texture.
		 * @return Raw texture.
		*/
		virtual void* getRawData() override;

		/**
		 * @brief Set data to texture.
		 * @param data New data.
		 * @param size Data size in bytes.
		 * @param offset Data offset from beginning.
		*/
		virtual void setData(void* data, UInt size, const Math::Vector2Int& offset = Math::Vector2Int::zero()) override;

		/**
		 * @brief Bind texture to a certain slot.
		 * @param slot The slot.
		*/
		virtual void bindToSlot(UInt slot = 0) const override;

		/**
		 * @brief Check if two textures are equal to each other.
		 * @param other The other texture.
		*/
		virtual bool operator ==(const Texture2D& other) const override;

		/**
		 * @brief Check if two textures differ to each other.
		 * @param other The other texture.
		*/
		virtual bool operator !=(const Texture2D& other) const override;

	private:

		std::string _path;
		UInt _width, _height;
		UInt _rendererID;
		UInt _internalFormat, _dataFormat;
	};

}
