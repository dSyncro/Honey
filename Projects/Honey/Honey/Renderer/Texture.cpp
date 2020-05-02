#include "Texture.h"

#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLTexture.h>

using namespace Honey;

Reference<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLTexture2D>(width, height);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Reference<Texture2D> Texture2D::Create(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLTexture2D>(path);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}