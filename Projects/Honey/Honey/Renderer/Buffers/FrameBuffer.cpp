#include "FrameBuffer.h"

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/Buffers/OpenGLFrameBuffer.h>

using namespace Honey;

Reference<FrameBuffer> Honey::FrameBuffer::Create(const FrameBufferSpecification& specification)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateReference<OpenGLFrameBuffer>(specification);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
