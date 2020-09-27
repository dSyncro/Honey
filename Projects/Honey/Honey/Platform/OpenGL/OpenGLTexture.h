#pragma once

#include <Honey/Renderer/Texture.h>

namespace Honey {

	class OpenGLTexture2D final : public Texture2D {

	public:

		OpenGLTexture2D(std::size_t width, std::size_t height, PixelFormat format);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual std::size_t GetWidth() const override { return _width; }
		virtual std::size_t GetHeight() const override { return _height; }

		virtual void* GetRawData() override;
		virtual void SetData(void* data, std::size_t size, const Math::Vector2Int& offset = Math::Vector2Int::zero()) override;

		virtual void BindToSlot(uint32_t slot = 0) const override;

		virtual bool operator ==(const Texture2D& other) const override;
		virtual bool operator !=(const Texture2D& other) const override;

	private:

		std::string _path;
		std::size_t _width, _height;
		uint32_t _rendererID;
		unsigned int _internalFormat, _dataFormat;
	};

}
