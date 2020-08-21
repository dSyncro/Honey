#include "RenderCommand.h"

#include <Honey/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Honey;

Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

void RenderCommand::Init()
{
	s_RendererAPI->Init();
}

void RenderCommand::SetViewport(Math::Vector2 location, Math::Vector2 size)
{
	s_RendererAPI->SetViewport(location, size);
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	s_RendererAPI->SetViewport(x, y, width, height);
}

void RenderCommand::DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount)
{
	s_RendererAPI->DrawIndexed(vertexArray);
}
