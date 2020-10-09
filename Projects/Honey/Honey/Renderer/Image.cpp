#include "Image.h"

#include "stb_image.h"
#include <stb_image_write.h>

using namespace Honey;
using namespace Honey::Math;

Image::Image(UInt width, UInt height, UInt channels)
	: _width(width), _height(height), _channels(channels)
{
	_bitmap = new Byte[width * height * channels];
}

Image::~Image()
{
	free();
}

void Image::setData(Byte* data, UInt size, UInt offset)
{
	HNY_CORE_ASSERT(getSizeInBytes() >= offset + size, "Trying to draw outside image!");
	std::memcpy(_bitmap + offset, data, size);
}

Reference<Image> Image::create(UInt width, UInt height, UInt channels)
{
	return CreateReference<Image>(width, height, channels);
}

Reference<Image> Image::createFromFile(const std::string& path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	HNY_CORE_ASSERT(data, "Failed to load image!");

	Reference<Image> image = CreateReference<Image>(width, height, channels);
	image->setData(static_cast<Byte*>(data), image->getSizeInBytes());
	stbi_image_free(data);

	return image;
}

void Image::writeToPNG(const std::string& filename) const
{
	stbi_write_png(filename.c_str(), static_cast<int>(_width), static_cast<int>(_height), 1, _bitmap, static_cast<int>(_width * _channels));
}

void Image::free()
{
	if (_bitmap) delete[] _bitmap;
	_bitmap = nullptr;
}
