#include "Image.h"

#include "stb_image.h"

using namespace Honey;
using namespace Honey::Math;

Image::Image(std::size_t width, std::size_t height, std::size_t channels)
	: _width(width), _height(height), _channels(channels)
{
	_bitmap = new std::byte[width * height * channels];
}

Image::~Image()
{
	Free();
}

void Image::SetData(std::byte* data, std::size_t size, std::size_t offset)
{
	HNY_CORE_ASSERT(GetSizeInBytes() >= offset + size, "Trying to draw outside image!");
	std::memcpy(_bitmap + offset, data, size);
}

Reference<Image> Image::Create(std::size_t width, std::size_t height, std::size_t channels)
{
	return CreateReference<Image>(width, height, channels);
}

Reference<Image> Image::CreateFromFile(const std::string& path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	HNY_CORE_ASSERT(data, "Failed to load image!");

	Reference<Image> image = CreateReference<Image>(width, height, channels);
	image->SetData((std::byte*)data, image->GetSizeInBytes());
	stbi_image_free(data);

	return image;
}

void Image::Free()
{
	if (_bitmap) delete[] _bitmap;
	_bitmap = nullptr;
}
