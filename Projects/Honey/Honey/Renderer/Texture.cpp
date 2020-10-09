#include "Texture.h"

#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLTexture.h>

using namespace Honey;

Reference<Texture2D> Texture2D::create(UInt width, UInt height, PixelFormat format)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLTexture2D>(width, height, format);
		case RendererAPI::API::DirectX: HNY_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Reference<Texture2D> Texture2D::create(const std::string& path)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLTexture2D>(path);
		case RendererAPI::API::DirectX: HNY_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
