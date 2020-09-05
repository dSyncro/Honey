#pragma once

#include <cstddef>
#include <Honey/Math/Math.h>

namespace Honey {

	class Image {

	public:

		Image(std::size_t width, std::size_t height, std::size_t channels = 3);
		~Image();

		void SetData(std::byte* data, std::size_t size, std::size_t offset = 0);

		static Reference<Image> Create(std::size_t width, std::size_t height, std::size_t channels = 3);
		static Reference<Image> CreateFromFile(const std::string& path);

		std::byte* GetRawBitmap() const { return _bitmap; }

		std::size_t GetWidth() const { return _width; }
		std::size_t GetHeight() const { return _height; }
		std::size_t GetChannels() const { return _channels; }

		std::size_t GetPixelCount() const { return _width * _height; }
		std::size_t GetSizeInBytes() const { return GetPixelCount() * _channels; }
		std::size_t GetStride() const { return _width * _channels; }

		Math::Size GetSize() const { return Math::Size(_width, _height); }

	private:

		void Free();

		std::byte* _bitmap;

		std::size_t _width;
		std::size_t _height;
		std::size_t _channels;

	};

}
