#include "VertexArray.h"

#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLVertexArray.h>

using namespace Honey;

Reference<VertexArray> VertexArray::create()
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLVertexArray>();
		case RendererAPI::API::DirectX: HNY_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
