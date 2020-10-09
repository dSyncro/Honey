#pragma once

#include <cstddef>

#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Image representation.
	*/
	class Image {

	public:

		/**
		 * @brief Construct Image from its components.
		 * @param width Image width.
		 * @param height Image height.
		 * @param channels Image channels.
		*/
		Image(UInt width, UInt height, UInt channels = 3);
		~Image();

		/**
		 * @brief Set new data to image.
		 * @param data New data.
		 * @param size Size of data in byte.
		 * @param offset Offset from beginning.
		*/
		void setData(Byte* data, UInt size, UInt offset = 0);

		/**
		 * @brief Create a new Image.
		 * @param width Image width.
		 * @param height Image height.
		 * @param channels Image channels.
		 * @return A new memory managed Image.
		*/
		static Reference<Image> create(UInt width, UInt height, UInt channels = 3);

		/**
		 * @brief Create a new Image from file.
		 * @param path File path.
		 * @return A new memory managed file loaded from disk.
		*/
		static Reference<Image> createFromFile(const std::string& path);

		/**
		 * @brief Get underlying bitmap.
		 * @return Raw bitmap.
		*/
		Byte* getRawBitmap() const { return _bitmap; }

		/**
		 * @brief Get image width.
		 * @return The width.
		*/
		UInt getWidth() const { return _width; }

		/**
		 * @brief Get image height.
		 * @return The height.
		*/
		UInt getHeight() const { return _height; }

		/**
		 * @brief Get image channels.
		 * @return The channels.
		*/
		UInt getChannels() const { return _channels; }

		/**
		 * @brief Get image pixel count.
		 * @return Pixel count.
		*/
		UInt getPixelCount() const { return _width * _height; }

		/**
		 * @brief Get image size in byte.
		 * @return Size in bytes.
		*/
		UInt getSizeInBytes() const { return getPixelCount() * _channels; }

		/**
		 * @brief Get image stride.
		 * @return Stride.
		*/
		UInt getStride() const { return _width * _channels; }

		/**
		 * @brief Get image size.
		 * @return Size.
		*/
		Math::Size getSize() const { return Math::Size(_width, _height); }

		/**
		 * @brief Write image to a PNG file.
		 * @param filename Image file path.
		*/
		void writeToPNG(const std::string& filename) const;

	private:

		void free();

		Byte* _bitmap;

		UInt _width;
		UInt _height;
		UInt _channels;

	};

}
