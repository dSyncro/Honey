#include "IndexBuffer.h"

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/Buffers/OpenGLIndexBuffer.h>

using namespace Honey;

Reference<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}