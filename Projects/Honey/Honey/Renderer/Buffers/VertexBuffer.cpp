#include "VertexBuffer.h"

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/Buffers/OpenGLVertexBuffer.h>

using namespace Honey;

Reference<VertexBuffer> VertexBuffer::create(UInt size)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLVertexBuffer>(size);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}


Reference<VertexBuffer> VertexBuffer::create(Float* vertices, UInt size)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLVertexBuffer>(vertices, size);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
