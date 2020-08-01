#pragma once

#include <Honey/Renderer/Texture.h>

namespace Honey {

	class OpenGLTexture2D final : public Texture2D {

	public:

		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return _width; }
		virtual uint32_t GetHeight() const override { return _height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator ==(const Texture2D& other) const override;
		virtual bool operator !=(const Texture2D& other) const override;

	private:

		std::string _path;
		uint32_t _width, _height;
		uint32_t _rendererID;
		unsigned int _internalFormat, _dataFormat;
	};

}
