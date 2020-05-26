#include "OpenGLTexture.h"

using namespace Honey;

#include <stb_image.h>

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
	: _width(width), _height(height)
{
	HNY_PROFILE_FUNCTION();

	_internalFormat = GL_RGBA8;
	_dataFormat = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
	glTextureStorage2D(_rendererID, 1, _internalFormat, _width, _height);

	glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : _path(path)
{
	HNY_PROFILE_FUNCTION();

	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(_path.c_str(), &width, &height, &channels, 0);
	HNY_CORE_ASSERT(data, "Failed to load image!");

	_width = width;
	_height = height;

	if (channels == 4)
	{
		_internalFormat = GL_RGBA8;
		_dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		_internalFormat = GL_RGB8;
		_dataFormat = GL_RGB;
	}

	HNY_CORE_ASSERT(_internalFormat & _dataFormat, "Format not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
	glTextureStorage2D(_rendererID, 1, _internalFormat, _width, _height);

	glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	HNY_PROFILE_FUNCTION();

	glDeleteTextures(1, &_rendererID);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	HNY_PROFILE_FUNCTION();

	uint32_t bpp = _dataFormat == GL_RGBA ? 4 : 3;
	HNY_CORE_ASSERT(size == _width * _height * bpp, "Provided size does not equal texture size");
	glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	HNY_PROFILE_FUNCTION();

	glBindTextureUnit(slot, _rendererID);
}

bool OpenGLTexture2D::operator ==(const Texture2D& other) const
{
	return ((const OpenGLTexture2D&)other)._rendererID == _rendererID;
}

bool OpenGLTexture2D::operator !=(const Texture2D& other) const
{
	return !(*this == other);
}