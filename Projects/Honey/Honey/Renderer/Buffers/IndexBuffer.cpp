#include "IndexBuffer.h"

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/Buffers/OpenGLIndexBuffer.h>

using namespace Honey;

Reference<IndexBuffer> IndexBuffer::create(UInt* indices, UInt count)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLIndexBuffer>(indices, count);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
