#pragma once

#include <Honey/Renderer/Texture.h>

namespace Honey {

	class OpenGLTexture2D final : public Texture2D {

	public:

		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return _width; }
		virtual uint32_t GetHeight() const override { return _height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:

		std::string _path;
		uint32_t _width, _height;
		uint32_t _rendererID;
	};

}