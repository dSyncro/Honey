#include "RendererAPI.h"

#include <Honey/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Honey;

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

Unique<RendererAPI> RendererAPI::create()
{
	switch (s_API)
	{
		case RendererAPI::API::None:    HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateUnique<OpenGLRendererAPI>();
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
