#include "GraphicsContext.h"

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>

using namespace Honey;

Unique<GraphicsContext> GraphicsContext::Create(void* window)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateUnique<OpenGLContext>(static_cast<void*>(window));
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
