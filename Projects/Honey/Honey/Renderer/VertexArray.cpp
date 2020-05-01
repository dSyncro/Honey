#include "VertexArray.h"

#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLVertexArray.h>

using namespace Honey;

Reference<VertexArray> VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLVertexArray>();
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}