#include "VertexBuffer.h"

#include <Honey/Core.h>

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/Buffers/OpenGLVertexBuffer.h>

using namespace Honey;

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
