#include "OpenGLTexture.h"

using namespace Honey;
using namespace Honey::Math;

#include <Honey/Core.h>

#include <stb_image.h>

extern "C" {
#include <glad/glad.h>
}

static GLenum ChannelToGL(Texture::Channel channel)
{
	switch (channel)
	{
		default:
		case Texture::Channel::Red: return GL_RED;
		case Texture::Channel::Green: return GL_GREEN;
		case Texture::Channel::Blue: return GL_BLUE;
		case Texture::Channel::Alpha: return GL_ALPHA;
	}
}

static GLenum PixelToDataFormat(Texture::PixelFormat format)
{
	switch (format)
	{
		default:
		case Texture::PixelFormat::R: return GL_RED;
		case Texture::PixelFormat::RG: return GL_RG;
		case Texture::PixelFormat::RGB: return GL_RGB;
		case Texture::PixelFormat::BGR: return GL_BGR;
		case Texture::PixelFormat::RGBA: return GL_RGBA;
		case Texture::PixelFormat::BGRA: return GL_BGRA;
	}
}

static uint32_t DataFormatToBPP(GLenum dataFormat)
{
	switch (dataFormat)
	{
		case GL_R: default: return 1;
		case GL_RG: return 2;
		case GL_RGB: return 3;
		case GL_RGBA: return 4;
	}
}

static GLenum DataFormatToInternalFormat(GLenum dataFormat)
{
	switch (dataFormat)
	{
		case GL_R: default: return GL_R8;
		case GL_RG: return GL_RG8;
		case GL_RGB: return GL_RGB8;
		case GL_RGBA: return GL_RGBA8;
	}
}

static Texture::PixelFormat PixelFormatFromChannels(std::size_t channels, bool reverse = false)
{
	switch (channels)
	{
		case 1: return Texture::PixelFormat::R;
		case 2: return Texture::PixelFormat::RG;
		case 3: return reverse ? Texture::PixelFormat::BGR : Texture::PixelFormat::RGB;
		case 4: default: return reverse ? Texture::PixelFormat::BGRA : Texture::PixelFormat::RGBA;
	}
}

OpenGLTexture2D::OpenGLTexture2D(std::size_t width, std::size_t height, PixelFormat format)
	: _width(width), _height(height)
{
	HNY_PROFILE_FUNCTION();

	_dataFormat = PixelToDataFormat(format);
	_internalFormat = DataFormatToInternalFormat(_dataFormat);

	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
	glTextureStorage2D(_rendererID, 1, _internalFormat, _width, _height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

	GLenum internalFormat = 0, dataFormat = 0;

	dataFormat = PixelToDataFormat(PixelFormatFromChannels(channels));
	internalFormat = DataFormatToInternalFormat(dataFormat);

	_internalFormat = internalFormat;
	_dataFormat = dataFormat;

	HNY_CORE_ASSERT(_internalFormat & _dataFormat, "Format not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
	glTextureStorage2D(_rendererID, 1, _internalFormat, _width, _height);

	glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

void* OpenGLTexture2D::GetRawData()
{
	void* data = nullptr;
	glGetTextureImage(_rendererID, 0, _dataFormat, GL_UNSIGNED_BYTE, _width * _height, data);
	return data;
}

void OpenGLTexture2D::SetData(void* data, std::size_t size, const Vector2Int& offset)
{
	HNY_PROFILE_FUNCTION();

	uint32_t bpp = DataFormatToBPP(_dataFormat);
	HNY_CORE_ASSERT(size == _width * _height * bpp, "Provided size does not equal texture size");
	glTextureSubImage2D(_rendererID, 0, offset.x, offset.y, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::BindToSlot(uint32_t slot) const
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
