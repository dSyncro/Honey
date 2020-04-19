#include "VertexArray.h"

#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLVertexArray.h>

using namespace Honey;

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}